import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse
import os

visited = set()

def is_directory_link(href):
    return href.endswith('/')

def is_readme_link(href):
    name = href.rstrip('/').split('/')[-1].lower()
    return name.startswith('readme')

def crawl(url, session, out_handle):
    """Recursively crawl `url`, appending any README* files to out_handle."""
    if url in visited:
        return
    visited.add(url)

    resp = session.get(url)
    resp.raise_for_status()
    soup = BeautifulSoup(resp.text, 'html.parser')

    for a in soup.find_all('a', href=True):
        href = a['href']
        full = urljoin(url, href)

        if urlparse(full).netloc != urlparse(url).netloc:
            continue

        if is_readme_link(href):
            r = session.get(full)
            r.raise_for_status()
            out_handle.write(r.text)

        elif is_directory_link(href):
            crawl(full, session, out_handle)

if __name__ == '__main__':
    BASE = 'http://10.14.59.11/.hidden/'
    sess = requests.Session()

    with open('all_readmes.txt', 'w', encoding='utf-8') as out:
        crawl(BASE, sess, out)

    print("Done! All READMEs consolidated into all_readmes.txt")
