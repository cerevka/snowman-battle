# Client #

Třída, jejíž instance se vytváří pouze ve chvíli, kdy se hráč připojuje k server. Při svém vzniku se vytváří QSocket, který se připojuje na zadanou adresu v síti. Po připojení okamžitě obdržuje od serveru své ID, pod kterým se bude celou dobu ve hře identifikovat. Jako odpověď zasílá serveru jméno, pod kterým chce být viděn ostatními hráči.

## Hello packety ##

Klient při svém vzniku spouští po připojení se k serveru časovač, který v pravidelných intervalech odesílá tzv. "Hello packety", kterými serveru indikuje, že stále žije. Jejich zpracování dále řídí server, nicméně bez těchto packetů je hráč ze hry odstaven.

## Herní logika ##

Klient nezpracování žádnou herní logiku, jeho jediným úkolem je odesílat data o svých akcích serveru a následně přijímat již vyhodnocené instrukce a pouze je zobrazovat hráči.