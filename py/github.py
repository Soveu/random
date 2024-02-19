import json
from collections import defaultdict
from urllib.request import urlopen
from functools import reduce

user = "Soveu"
repos = json.loads(urlopen(f"https://api.github.com/users/{user}/repos?per_page=100").read())

print("Repos:")
print(repos)

def reducer(stats, lang_url):
    print(f"Getting {lang_url}")
    info = json.loads(urlopen(lang_url).read())
    print(info)
    for (lang, lines) in info.items():
        stats[lang] += lines
    return stats 

lang_stats = reduce(reducer, (repo["languages_url"] for repo in repos), defaultdict(int))
print("Lang stats:")
print(lang_stats)
