#![feature(proc_macro_hygiene, decl_macro)]
#[macro_use] extern crate rocket;
mod database;
use rocket::State;
use postgres::Client;
use std::sync::Mutex;
use std::time::Instant;

struct DBMutex {
    mutex : Mutex<Client>
}

#[get("/")]
fn world(client_mutex : State<DBMutex>) -> String {
    let mut client = client_mutex.inner().mutex.lock().unwrap();
    let before = Instant::now();
    let words = database::get_n_words(&mut client, 1000).unwrap();
    println!("request words {:.2?}", before.elapsed());
    let result : String = words.join(" ");
    result
}

fn main() {
    let db_mutex = DBMutex {
        mutex: Mutex::new(database::init_connection("127.0.0.1", "test_db", "test_user", "12345678").unwrap())
    };

    rocket::ignite()
    .mount("/words", routes![world])
    .manage(db_mutex)
    .launch();
}

//
//#![feature(proc_macro_hygiene, decl_macro)]
//
//#[macro_use] extern crate rocket;
//
//
//
//
//
//fn main() {
//    println!("test");
//
//    let bytes = include_bytes!("../words/russian.txt");
//    let string_data = String::from_utf8_lossy(bytes);
//    let mut words: Vec<&str> = string_data.split('\n').collect();
//
//
//
//    let before = Instant::now();
//    let first_words = database::get_n_words(&mut client, 100).unwrap();
//    let elapsed = before.elapsed();
//    println!("Request elapsed time: {:.2?}", before.elapsed());
//    for word in first_words {
//        println!("{}", word);
//    }
//}
//
//
//
