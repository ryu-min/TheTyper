mod database;

extern crate rocket;
use std::time::Instant;


//use rocket::{
//    serde::{json::Json, Deserialize, Serialize},
//};
//
//#[derive(Deserialize, Serialize)]
//struct WordsResponse {
//    words: String,
//}

//#[rocket::get("/words", format = "json")]
//fn get_words() -> Json<WordsResponse> {
//    let words: String = String::from("Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. \
//                                         Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. \
//                                         Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. \
//                                         Words are the basic building blocks of grammar. \
//                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
//                                         Some words contain more than one part, such as hyphenated words and other compound words. \
//                                         Some words are pronounced in the same way but carry different meanings. ");
//    Json( WordsResponse { words } )
//}

fn main() {
    println!("test");

    let bytes = include_bytes!("../words/russian.txt");
    let string_data = String::from_utf8_lossy(bytes);
    let mut words: Vec<&str> = string_data.split('\n').collect();

    let mut client = database::init_connection("127.0.0.1", "test_db", "test_user", "12345678").unwrap();

//    let mut words = Vec::new();
//    words.push("other1");
//    words.push("other2");
//    words.push("other3");
//    words.push("othet4");
//    words.push("other5");
    let before = Instant::now();
    let first_words = database::get_n_words(&mut client, 1000).unwrap();
    let elapsed = before.elapsed();
    for word in first_words {
        println!("{}", word);
    }
    println!("Request elapsed time: {:.2?}", elapsed);
}

