# Comprehension
creazione di liste iterando attraverso altre liste
```py
my_list = [x**2 for x in range(10)]
print(my_list )
# [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]

# posso otteenre qualsiasi cosa in output, anche una stringa formattata
my_list = [f"{x}^2 = {x**2}" for x in range(10)]
print(my_list )

# posso anche innestarle
[(x, y) for x in range(10) for y in range(8)]
# mi spara fuori tutte le combinazioni
```

# Lambda function
```py
lambda x : x+1
```
prende x e restituisce x+1

```py
a = [1, -2, -4, 3, 5, 6]

print (sorted(a))
# [-4, -2, 1, 3, 5, 6]

print (sorted(a, key = lamda x: abs(x)))
# [1, -2, 3, -4, 5, 6]
```

in python ogni cosa è un oggetto, passato per reference -> cio che cambio in una funzione cambia anche nello scope globale

# Classi

`__init__` è il costruttore. non c'è dichiarazione dei campi / interfaccia pubblica. se dichiaro una variabile fuori da una funzione, essa è statica. non c'è keyword new, ogni metodo deve avere un parametro self (self è nome convenzionale, ma puoi chiamarlo come vuoi). quest'ultimom non deve essere passato quando si chiama il metodo.

```py
class Point:
    ## costruttore
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def distance(self, p):
        return math.sqrt((self.x - p.x)**2 + (self.y - p.y) **2)

p = Point(2.0, 6.0)
# non c'è la keywork new

class Dog:
    tricks = [] # variabile statica di classe
    def __init__(self, name):
        self.name = name
```

si possono estendere classi

```py
class DogwithPedigree(Dog):
    def __init__(self, name, parent):
        Dog.__init__(self, name, parent)
        self.parent = parent
```

Valgono le regole dell'overriding
