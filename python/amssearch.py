import urllib
import urllib2
import cookielib
import re
from bs4 import BeautifulSoup

# pstdata = [ ('pg4', 'AUCN'), ('s4', 'Deng, Weihua'), ('co4', 'AND'),
            # ('pg5', 'TI'),   ('s5', ''), ('co5', 'AND'),
            # ('pg6', 'PC'),   ('s6', ''), ('co6', 'AND'),
            # ('pg7', 'ALLF'), ('s7', ''), ('co7', 'AND'),
            # ('dr' , 'all' ), ('yrop', 'eq'), ('arg3', ''),
            # # ('dr' , 'pubyear' ), ('yrop', 'eq'), ('arg3', '=2012'),
            # # ('dr', 'pubyear'), ('yearRangeFirst', ''), ('yearRangeSecond', ''),
            # ('pg8', 'ET'), ('s8', 'All'),
            # # ('pg8', 'ET'), ('s8', 'Journals'),
            # ('review_format', 'PDF'), 
            # ('Submit', 'Search'), 
            # ('r', '5')]

# amsurl = 'http://www.ams.org/mathscinet/search/publications.html'
amsurl = 'http://www.ams.org/mathscinet/search/journals.html'
pstdata = [('journalName', 'Applied and Computational Harmonic Analysis'),
               ('Submit','Search')]
hds = {'User-Agent' :'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/48.0.2564.116 Safari/537.36'}

cookie = cookielib.CookieJar()
cookie_handler = urllib2.HTTPCookieProcessor(cookie)
dt = urllib.urlencode(pstdata)
req = urllib2.Request(url = amsurl, data = dt, headers = hds)
opener = urllib2.build_opener(cookie_handler)

response = opener.open(req)
page = response.read()
soup = BeautifulSoup(page, "html.parser")

h2 = soup.find('h2')
h2text = h2.get_text().encode('utf-8')

jdoc = soup.find('div', attrs={'class':'jdoc'})
jdoctext = jdoc.get_text().encode('utf-8')

print h2text
print re.sub(r'\n{2,}', '\n\n', jdoctext, re.M)

# for item in soup.find_all('div', attrs={'class':'headlineText'}):
    # # print item.find_all('a')
    # print item.get_text().encode('utf-8')

