voglio prima fare un binary classifier tra 
* è problmeatico 
* non è problematico. 

voglio tantissima specificità sui non problmeatici, ovvero voglio che quelli che classifico come non problematici siano effetivamente tali. gli altri possono anche essere falsi positivi. ma poi indago meglio. questo perché non voglio mancarmi nessun positivo. quindi inzialmente faccio quello. poi uso un altro algoritmo, sul dataset di quelli che ho segnalati come positivi, per cotrollare le varie classi (negativo compreso).
cioè true negative = 100%