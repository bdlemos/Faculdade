# Auto Upload Fact-Check Dataset
# Runing at Python 3.5.6
# Feeds:
# https://aosfatos.org/noticias/feed/
# https://apublica.org/feed/
# https://piaui.folha.uol.com.br/lupa/feed/

import pandas as pd
import feedparser
# To text preprocessing
import xml.sax.saxutils as saxutils
import ast
import re
# To get claimReview
from bs4 import BeautifulSoup
import requests

# Get links list from websites feed
def get_articles_url(url):
    d = feedparser.parse(url)
    linksList = []
    for post in d.entries: linksList.append(post.link)
    return linksList

# Save dataset to tsv file
def save_tsv_pandas(data, file_name):
    data.to_csv("./" + file_name + ".tsv", sep='\t',index=True)

# Load dataset from tsv file
def load_tsv_pandas(file_name):
    return pd.read_csv(file_name+".tsv", sep='\t', index_col=0)

# Update dataset. URL is primary key.
def update_dataset(dataset, new_entries):
    # Remove colunas que são todas NA em new_entries
    new_entries = new_entries.dropna(axis=1, how='all')
    # Remove colunas que são todas NA em dataset (opcional)
    dataset = dataset.dropna(axis=1, how='all')
    # Concatena os DataFrames
    temp_df = pd.concat([dataset, new_entries], axis=0)
    # Remove duplicatas do DataFrame resultante
    temp_df = temp_df.drop_duplicates()
    return temp_df

def re_char(str):
    return re.sub('[^A-Za-z0-9 \!\@\#\$\%\&\*\:\,\.\;\:\-\_\"\'\]\[\}\{\+\á\à\é\è\í\ì\ó\ò\ú\ù\ã\õ\â\ê\ô\ç\|]+', '',str)

# Text Preprocessing
def text_pre_proc(str):
    aux = saxutils.unescape(str.replace('&quot;', ''))
    #remove not allowed characters
    aux = re.sub('[^A-Za-z0-9 \!\@\#\$\%\&\*\:\,\.\;\:\-\_\"\'\]\[\}\{\+\á\à\é\è\í\ì\ó\ò\ú\ù\ã\õ\â\ê\ô\ç\|]+', '',aux)
    my_dict = ast.literal_eval(aux)
    return my_dict

# Get ClaimReview
def get_claimReview(url):
    response = requests.get(url, timeout=30)
    content = BeautifulSoup(response.content, "html.parser")
    claimList = []
    for claimR in content.findAll('script', attrs={"type": "application/ld+json"}):
        linha = []
        try:
            my_dict = text_pre_proc(claimR.get_text(strip=True))
            #print(my_dict)
            linha.append(url)
            linha.append(my_dict['author']['url'])
            linha.append(my_dict['datePublished'])
            linha.append(my_dict['claimReviewed'])
            try: linha.append(my_dict['reviewBody'])
            except:
                try:
                    linha.append(my_dict['description'])
                except:
                    linha.append('Empty')
            linha.append(re_char(content.title.get_text().replace('<title>','').replace('</title>','')))
            linha.append(my_dict['reviewRating']['ratingValue'])
            linha.append(my_dict['reviewRating']['bestRating'])
            linha.append(my_dict['reviewRating']['alternateName'])
            linha.append(my_dict['itemReviewed']['@type'])
            claimList.append(linha)
        except Exception as e:
            print ("Erro: " + str(e))
            pass
    return claimList

# Main Function
def main():
    websites = ["https://aosfatos.org/noticias/feed/", "https://apublica.org/tag/truco/feed/", "https://piaui.folha.uol.com.br/lupa/feed/"]
    toprow = ['URL', 'Author', 'datePublished', 'claimReviewed', 'reviewBody', 'title', 'ratingValue', 'bestRating', 'alternativeName', 'contentType']
    # Step 1 - Get links list of the last articles
    linksList = []
    for url in websites: linksList.extend(get_articles_url(url))
    print ("Numero de links: {}".format(len(linksList)))
    # Step 2 - Get Claim Review
    claimList = []
    count = 0
    for url in linksList:
        count = count + 1
        #print ("{} de {} > ".format(count,len(linksList)) + url)
        lineList = get_claimReview(url)
        #input("Press Enter to continue...")
        for line in lineList: claimList.append(line)
    # Step 3 - Create pandas DataFrame with the new entries
    new_entries = pd.DataFrame(claimList, columns=toprow)
    new_entries = new_entries.set_index('URL')
    print ("Numero de entradas: {}".format(len(new_entries)))
    print (new_entries)
    # Step 4 - Load the old version of the dataset, update and save
    dataset = load_tsv_pandas('FACTCKBR')
    factCkBr = update_dataset(dataset, new_entries)
    save_tsv_pandas(factCkBr, 'new_factCkBR')

if __name__ == "__main__":
    main()