import requests
import json

with open('secret.json', 'r') as secretfp:
    COOKIE = json.load(secretfp)['COOKIE']


with open('booklist.json', 'r') as booksfp:
    BOOKS = json.load(booksfp)['books']



def text_result(book_id: str, query: str):
    headers = {
        'cookie': COOKIE
    }
    resp = requests.get(
        f'https://books.google.co.jp/books?id={book_id}&jscmd=SearchWithinVolume&q={query}',
        headers=headers
    )
    return resp.json()


book_id = 'wY75DwAAQBAJ'
query = 'インターネット'
print(text_result(book_id, query))
