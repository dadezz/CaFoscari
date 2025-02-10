import re

with open(r"C:\\Users\\Dav\\Downloads\\saw-enigma.txt", mode='r') as file:
    content = file.read()
    url_pattern = r"https?://(www\.)?[A-Za-z0-9-]+(\.[a-zA-Z]{2,})+(/[\w\-\.~!$&'()*+,;=]*)(\?[A-Za-z0-9\-._~!$&'()*+,;=]*)(#[A-Za-z0-9\-._~!$&'()*+,;=]*)?"
  
    result = re.findall(url_pattern, content)

    print(result)


with open(r"C:\\Users\\Dav\\Downloads\\saw-enigma-the-return.txt", mode='r') as file:
    content = file.read()

    # what is 16 characters long, either starts or ends with a star, and alternates between a letter and a digit?
    url_pattern = r"\*[A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z]"
    result = re.findall(url_pattern, content)
    print("starts with a star and a letter")
    print(result)

    url_pattern = r"[A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z]\*"
    result = re.findall(url_pattern, content)
    print("starts with a letter end with a star")
    print(result)

    url_pattern = r"\*[0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9]"
    result = re.findall(url_pattern, content)
    print("starts with a star and a number")
    print(result)

    url_pattern = r"[0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9][A-Za-z][0-9]\*"
    result = re.findall(url_pattern, content)
    print("starts with a star and a number")
    print(result)
