use postgres::{Client, NoTls, Error};

pub fn init_connection(host : &str, db_name: &str,
                       user_name: &str, user_password: &str ) -> Result<Client, Error> {
    let params = format!("host={} dbname={} user={} password={}",
                          host, db_name, user_name, user_password );
    let mut client : Client = Client::connect(params.as_str(), NoTls)?;
    check_word_table(&mut client)?;
    Ok(client)
}

pub fn append_words(client : &mut Client, words: Vec<&str> ) -> Result<(), Error> {
    let mut transaction = client.transaction()?;
    for word in words {
        transaction.query(
                    "INSERT INTO words  VALUES ($1)",
            &[&word])?;
    }
    transaction.commit()?;
    Ok(())
}

pub fn get_words(client : &mut Client ) -> Result<Vec<String>, Error> {
    let mut result : Vec<String> = Vec::new();
    for row in client.query("SELECT * FROM words", &[])? {
        let word: &str = row.get(0);
        result.push(word.to_string());
    }
    Ok(result)
}

pub fn get_n_words(client: &mut Client, count : usize) -> Result<Vec<String>, Error> {
    let mut result = Vec::with_capacity(count);
    let query_string = format!("SELECT * FROM words ORDER BY random() LIMIT {}", count);
    for row in client.query(&query_string, &[])? {
        let word: &str = row.get(0);
        result.push(word.to_string());
    }
    Ok(result)
}

pub fn is_empty(client: &mut Client) -> Result<bool, Error> {
    let mut count : i64 = 0;
    for result in client.query("SELECT COUNT(*) FROM words", &[])? {
        count = result.get(0);
        break;
    }
    println!("count is {}", count);
    Ok(count == 0)
}

pub fn clear(client: &mut Client) -> Result<(), Error> {
    client.query("DELETE FROM words", &[])?;
    Ok(())
}

fn check_word_table(client : &mut Client) -> Result<(), Error> {
    let mut contais_words_table: bool = false;
    for result in client.query("SELECT table_name from information_schema.tables", &[])? {
        let table_name : &str = result.get(0);
        if table_name == "words" {
            contais_words_table = true;
            break;
        };
    }
    if !contais_words_table {
        client.batch_execute("
        CREATE TABLE words (
        word    TEXT PRIMARY KEY
        )")?;
    }
    Ok(())
}