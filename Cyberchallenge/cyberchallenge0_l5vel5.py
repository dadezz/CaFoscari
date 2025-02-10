
import json
import requests


dic = {}
with open(r"C:\\Users\\Dav\\Uni_Lavoro\\CaFoscari\\Cyberchallenge\\questions.json", mode="r") as questions:
    # Load JSON content directly from the file object
    result = json.load(questions)
    
    # Assuming result is a list of questions
    for question in result:
        q = question["question"]
        a = question["answer"]
        dic.update({q: a})
    
    print(dic)


s=requests.Session()
response = s.post('https://ccit.waa.pt/kahs-wan/start', cookies={'session':'eyJwcm9ncmVzcyI6NSwicm9sZSI6InJvb2tpZSJ9.Z6c7Yw.fRx4PMTjdvn7qZaBgH86K2UYXjs'})


print (response.status_code)


responsej = response.json()

token = responsej["token"]
questions = responsej["questions"]

questions_list = []

for question in questions:
    questions_list.append(question["question"])

answers_list = []

for question in questions_list:
    answers_list.append(dic[question])

# Second POST request to submit the answers
data = {
    'token': token,
    'answers': answers_list
}
headers = {'Content-Type': 'application/json'}
response = s.post('https://ccit.waa.pt/kahs-wan/check', 
                  json=data, 
                  cookies={'session':'eyJwcm9ncmVzcyI6NSwicm9sZSI6InJvb2tpZSJ9.Z6c7Yw.fRx4PMTjdvn7qZaBgH86K2UYXjs'},
                  headers=headers)
print(response.status_code)

print(response.text)


