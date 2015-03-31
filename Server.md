# Server #

Základem každé hry je server, ke kterému se jednotliví klienti připojují. Bez server hra nemůže fungovat. Jakmile serveru přijde od klienta požadavek na spojení, odesílá mu identifikační ID a v odpovědi si bere jméno, které si klient zvolil. Po zahájení hry se rozešle server dvojice ID a jméno všem hráčům, aby se mezi sebou všichni znali. Veškeré zpráva, které server rozesílá, odesílá všem klientům. U chatových zpráv platí, že je při přijetí rozesílá všem klientům.

Pro komunikaci s klienti si server pro každého klienta zvlášť vytváří vlákno, ve kterém s ním komunikuje, aby mohl obsluhovat všechny klienty zároveň a nezávisle na sobě.

## Detekce lagů na síti ##

V případě, že některý hráč se dostane do "lagu" (tedy mu na chvíli vypadne síť), je úkolem serveru tento lag detekovat a dočasně ho postavit mimo hru s tím, že jakmile se opět ustálí spojení, klient bude moci pokračovat ve hře spolu s ostatními. Tato funkce je závislá na tzv. "Hello packetech", které jsou popsány v části "Client". Server si eviduje časy přijetí těchto packetů a stále si je aktualizuje. V nastaveném časovém intervalu si server kontroluje zpoždění hello packetů všech klientů a pokud je zpoždění některého z nich příliš velké, postaví ho mimo hru (sněhulák bude mít invertovány barvy) a informuje o tom všechny ostatní hráče. Postava hráče se pak tváří jako nezastřelitelná překážka.

## Herní logika ##

Na serveru běží veškeré vyhodnocování akcí, které obdržel od klientů, a následně rozesílá všem klientů instrukce, co se ve hře děje.