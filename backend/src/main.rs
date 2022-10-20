extern crate rocket;

use rocket::{
    serde::{json::Json, Deserialize, Serialize},
};

#[derive(Deserialize, Serialize)]
struct WordsResponse {
    words: String,
}

#[rocket::get("/words", format = "json")]
fn get_words() -> Json<WordsResponse> {
    let words: String = String::from("Words are the basic building blocks of grammar. \
                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
                                         Some words contain more than one part, such as hyphenated words and other compound words. \
                                         Some words are pronounced in the same way but carry different meanings. \
                                         Words are the basic building blocks of grammar. \
                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
                                         Some words contain more than one part, such as hyphenated words and other compound words. \
                                         Some words are pronounced in the same way but carry different meanings. \
                                         Words are the basic building blocks of grammar. \
                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
                                         Some words contain more than one part, such as hyphenated words and other compound words. \
                                         Some words are pronounced in the same way but carry different meanings. \
                                         Words are the basic building blocks of grammar. \
                                         Words are combinations of letters and sounds, individual words are separated by spaces. \
                                         Some words contain more than one part, such as hyphenated words and other compound words. \
                                         Some words are pronounced in the same way but carry different meanings. ");
    Json( WordsResponse { words } )
}

#[rocket::main]
async fn main() {
    if let Err(err) = rocket::build()
        .mount("/", rocket::routes![get_words])
        .launch()
        .await
    {
        println!("Rocket Rust couldn't take off successfully!");
        drop(err); // Drop initiates Rocket-formatted panic
    }
}