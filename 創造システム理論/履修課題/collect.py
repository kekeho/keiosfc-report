import json
import requests
import time
from typing import Dict, List


with open('booklist.json', 'r') as booksfp:
    books_json = json.loads(booksfp.read())


class Book():
    isbn: str
    image_url: str
    title: str
    description: str

    def __init__(self, isbn, image, title, desc) -> None:
        self.isbn = isbn
        self.image_url = image
        self.title = title
        self.description = desc

    def __str__(self) -> str:
        return f"({self.isbn}) {self.title}\n{self.description}\n{self.image_url}"

    def json_dict(self) -> Dict[str, str]:
        return {
            'isbn': self.isbn,
            'image': self.image_url,
            'title': self.title,
            'description': self.description,
        }


def google_books(isbn: str) -> Book:
    url = f"https://www.googleapis.com/books/v1/volumes?q=isbn:{isbn}"
    resp = requests.get(url)
    if resp.status_code != 200:
        raise Exception()

    book_json = resp.json()["items"]
    book_json = book_json[0]
    title = book_json["volumeInfo"]["title"]
    subtitle = ""
    try:
        subtitle = book_json["volumeInfo"]["subtitle"]
    except KeyError:
        pass
    description = book_json["volumeInfo"]["description"]
    image = book_json["volumeInfo"]["imageLinks"]["thumbnail"]

    book = Book(isbn, image, title + " " + subtitle, description)
    return book


def openbd(isbn: str) -> Book:
    url = f"https://api.openbd.jp/v1/get?isbn={isbn}"
    resp = requests.get(url)
    if resp.status_code != 200:
        raise Exception()

    book_json = resp.json()[0]
    title = book_json["onix"]["DescriptiveDetail"]["TitleDetail"]["TitleElement"]["TitleText"]["content"]
    subtitle = ""
    try:
        subtitle = book_json["onix"]["DescriptiveDetail"]["TitleDetail"]["TitleElement"]["Subtitle"]["content"]
    except KeyError:
        pass
    description = " ".join([x["Text"] for x in book_json["onix"]["CollateralDetail"]["TextContent"]])
    image = book_json["summary"]["cover"]
    book = Book(isbn, image, title + " " + subtitle, description)
    return book


books: List[Book] = []

for isbn in books_json:
    try:
        book = openbd(isbn)
    except Exception:
        print('openbd failed')
        try:
            book = google_books(isbn)
        except Exception:
            print('google failed')
            continue
    books.append(book)
    print(book)
    time.sleep(1)


with open('bookdata.json', 'w') as fp:
    json.dump([b.json_dict() for b in books], fp)
