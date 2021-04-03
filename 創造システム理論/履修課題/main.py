import requests
import janome
import json

with open('secret.json', 'r') as secretfp:
    COOKIE = json.load(secretfp)['COOKIE']


with open('bookdata.json', 'r') as booksfp:
    BOOKS = json.load(booksfp)


def search(query: str):
    booklist = []
    for book in BOOKS:
        if query in book['title']:
            booklist.append(book)
            continue
        if query in book['description']:
            booklist.append(book)
            continue
    return booklist


query = 'インターネット'
print(search(query))
