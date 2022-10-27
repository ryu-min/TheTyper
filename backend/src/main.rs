#![feature(proc_macro_hygiene, decl_macro)]
#[macro_use] extern crate rocket;
mod database;

#[get("/")]
fn world() -> String {
    let mut client = database::init_connection("127.0.0.1", "test_db", "test_user", "12345678").unwrap();
    let words = database::get_n_words(&mut client, 10).unwrap();
    let result : String = words.join(" ");
    result
}

fn main() {
    rocket::ignite().mount("/words", routes![world]).launch();
}

//
//#![feature(proc_macro_hygiene, decl_macro)]
//
//#[macro_use] extern crate rocket;
//
//use std::time::Instant;
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
