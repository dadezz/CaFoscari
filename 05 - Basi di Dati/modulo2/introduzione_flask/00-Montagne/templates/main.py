from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def index():
    mountains = ["Everest", "K2", "Gran Paradiso", "Civetta"]
    return render_template('./template_montagna.html', mountains = mountains) 
        # il primo mountains è la variabile nel file html,a cui assegno la mia lista

@app.route('/mountains/<mt>') # sto dichiarando la variabile mountains qui
def mountain(mt): # prendo come argomento lo stesso nome del link
    return "this is " + str(mt)

if __name__ == "__main__":
    app.run()
ss