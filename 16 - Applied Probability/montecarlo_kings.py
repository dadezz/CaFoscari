import random
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# --- 1. Funzione per simulare un singolo mescolamento e controllo ---
def check_adjacent_kings(deck):
    """
    Verifica se ci sono almeno due Re adiacenti in un mazzo mescolato.
    """
    # Mappa le carte a valori numerici per semplificare il controllo dei Re
    # Qui usiamo solo le prime 52 carte standard, i Kings sono 'K'
    
    # Crea il mazzo standard
    suits = ['Hearts', 'Diamonds', 'Clubs', 'Spades']
    ranks = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']
    
    # Costruisci un mazzo semplificato per la simulazione, dove i Re sono identificati chiaramente
    # Le altre carte sono 'non_K'
    sim_deck = ['K' if rank == 'K' else 'non_K' for rank in ranks for _ in suits]
    
    random.shuffle(sim_deck) # Mescola il mazzo
    
    # Controlla se ci sono Re adiacenti
    for i in range(len(sim_deck) - 1):
        if sim_deck[i] == 'K' and sim_deck[i+1] == 'K':
            return True # Trovati due Re adiacenti
    return False # Nessun Re adiacente trovato

# --- 2. Simulazione Monte Carlo ---
def run_monte_carlo_simulation(num_simulations):
    """
    Esegue la simulazione Monte Carlo per un dato numero di tentativi.
    Restituisce una lista delle probabilità stimate dopo ogni blocco di simulazioni.
    """
    results = []
    hits = 0
    
    # Per il grafico, vogliamo vedere la convergenza in passi più piccoli
    # Decidiamo quanti punti vogliamo nel grafico (es. 500 punti per 100k sim)
    points_to_plot = min(500, num_simulations) 
    step = max(1, num_simulations // points_to_plot)

    for i in range(1, num_simulations + 1):
        if check_adjacent_kings(None): # Il mazzo viene creato e mescolato internamente
            hits += 1
        
        if i % step == 0 or i == num_simulations: # Registra il risultato a intervalli regolari
            estimated_probability = hits / i
            results.append((i, estimated_probability))
            
    return np.array(results)

# --- 3. Calcolo della probabilità analitica (per confronto) ---
def calculate_analytical_probability():
    """
    Calcola la probabilità analitica che almeno due Re siano adiacenti.
    """
    # Totale modi di disporre i 4 Re in 52 posizioni: C(52, 4)
    # Modi in cui NESSUN Re è adiacente:
    # Immagina di posizionare prima le 48 non-Re. Questo crea 49 spazi dove i Re possono andare.
    # Se mettiamo i 4 Re in 4 spazi diversi (ognuno con 1 non-Re tra loro), non saranno adiacenti.
    # Quindi, scegliamo 4 spazi tra i 49: C(49, 4)
    
    # C(n, k) = n! / (k! * (n-k)!)
    from math import comb 
    
    total_arrangements = comb(52, 4) # Modi totali di scegliere 4 posizioni per i Re
    non_adjacent_arrangements = comb(49, 4) # Modi di scegliere 4 posizioni per i Re senza che siano adiacenti
    
    prob_no_adjacent = non_adjacent_arrangements / total_arrangements
    prob_at_least_one_adjacent = 1 - prob_no_adjacent
    return prob_at_least_one_adjacent

# --- Configurazione e esecuzione della simulazione ---
num_simulations = 200000 # Aumentato per una migliore convergenza nel video
print(f"Eseguendo {num_simulations} simulazioni Monte Carlo...")
monte_carlo_results = run_monte_carlo_simulation(num_simulations)

# Calcola la probabilità analitica
analytical_prob = calculate_analytical_probability()
print(f"Probabilità analitica di Re adiacenti: {analytical_prob:.6f}")
print(f"Stima Monte Carlo finale: {monte_carlo_results[-1, 1]:.6f}")

# --- 4. Generazione del grafico bello per YouTube ---
plt.style.use('seaborn-v0_8-darkgrid') # Stile per un aspetto moderno e pulito
plt.figure(figsize=(12, 7)) # Dimensioni per video (16:9)

# Plot dei risultati Monte Carlo
plt.plot(monte_carlo_results[:, 0], monte_carlo_results[:, 1], 
         color='#1f77b4', # Blu di default di Matplotlib
         linewidth=2.5, 
         label='Stima Monte Carlo')

# Plot della probabilità analitica
plt.axhline(y=analytical_prob, 
            color='red', 
            linestyle='--', 
            linewidth=2, 
            label=f'Probabilità Analitica ({analytical_prob:.4f})')

# Aggiungi un'etichetta al punto finale della simulazione
final_x = monte_carlo_results[-1, 0]
final_y = monte_carlo_results[-1, 1]
plt.scatter(final_x, final_y, color='red', s=100, zorder=5) # Punto finale più evidente
plt.annotate(f'{final_y:.4f}', 
             (final_x, final_y), 
             textcoords="offset points", 
             xytext=(0,10), 
             ha='center', 
             color='red', 
             fontsize=10, 
             weight='bold')

# Personalizzazione del grafico
plt.title(f'Convergenza della Stima Monte Carlo ({num_simulations:,} Simulazioni)', 
          fontsize=18, 
          weight='bold', 
          color='#333333')
plt.xlabel('Numero di Simulazioni', 
           fontsize=14, 
           color='#555555')
plt.ylabel('Probabilità Stimata di Re Adiacenti', 
           fontsize=14, 
           color='#555555')

plt.xscale('log') # Usa una scala logaritmica sull'asse X per mostrare meglio la convergenza iniziale
plt.xlim(10, num_simulations * 1.1) # Limiti dell'asse X
plt.ylim(0.15, 0.25) # Limiti dell'asse Y per ingrandire la zona di interesse

plt.grid(True, linestyle='--', alpha=0.6) # Griglia più leggera
plt.legend(fontsize=12) # Legenda con dimensione adeguata
plt.tick_params(labelsize=11, colors='#555555') # Colore e dimensione dei tick

plt.tight_layout() # Adatta i margini per evitare tagli
plt.show()

# --- Piccolo frame per lo screenshot del codice ---
# 
# def check_adjacent_kings(deck):
#     
#     random.shuffle(deck)
# 
#     # check if kings are adjacent
#     for i in range(len(deck) - 1):
#         if deck[i] == 'K' and deck[i+1] == 'K':
#             return True
#     return False
# 
# 
# def run_monte_carlo_simulations(n):
#     # Perform the Monte Carlo simulation for a given number n of attempts
# 
#     # deck creation
#     suits = ['Hearts', 'Diamonds', 'Clubs', 'Spades']
#     ranks = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A']
# 
#     # simulation deck
#     sim_deck = ['K' if rank == 'K' else 'non_K' for rank in ranks for _ in suits]
# 
#     results = []
#     hits = 0
# 
#     for i in range (1, n+1):
#         if check_adjacent_kings(sim_deck):
#             hits +=1
# 
#         estimated_probability = hits / i
#         results.append((i, estimated_probability))
# 
#     return results