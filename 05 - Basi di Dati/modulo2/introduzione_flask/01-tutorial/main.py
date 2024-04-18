from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def index():
    return "Hello world"

@app.route("/hello")
def hello():
    pass

@app.route("/greet/<name>")
def greet(name):
    return f"Hello, {name}"

@app.route("/at/<number1>/<number2>")
# posso forzare i numeri in url
# @app.route("/at/<int: number1>/<int: number2>")
def sum(number1, number2):
    return f"{int(number1) } + {int(number2)} = {int(number1)+int(number2)}"

"""
handle argument: 
posso creare un app route che mi prenda dall'url una richiesta 
e se la gestisca come vuole. posso quindi rifare la cosa fatta sopra su /num/num
in modo più elegante, gestendouna request

una request è un parametro che si mette dopo l'url. ha la forma di dizionario
"""
@app.route('/handle_url_params0')
def handle_params_example():
    return str(request.args())

"""
cosa mi ritorna sta roba se scrivo '127.0.0.1:5000/handle_request_params0'?

ImmutableMultiDict{[]}

prova ora ad aggiungere dei parametri in request:
'127.0.0.1:5000/handle_request_params0/?name=Mike&greeting=hello'

ImmutableMultiDict{[('name','Mike'), ('greeting', 'hello')]}

se ho parametri del genere, organizzati a dict, posso gestirmeli a mo di variabile

"""

@app.route('/handle_url_params')
def handle_params():
    # if one is missing, "BadRequestKeyError"
    # so, better check
    if 'greeting' in request.args.keys() and 'name' in request.args.keys():
        greeting = request.args.get('greeting')
        name = request.args['name'] # sintassi diversa ma sematica identica
        return f"{greeting}, {name}" # la page web conterrà "hello, Mike"
    else:
        return "keys missing"

"""
GET POST PUT DELETE
"""












if __name__ == '__main__':
    app.run(host = '0.0.0.0', port = 5000, debug = True)

