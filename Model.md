# Model #

## MVC ##

Aplikace stojí na třívrstvé architektuře Model - View - Controller, které hru rozděluje do tří logických celků.

### Model ###

Základní částí architektury je model, který v sobě uchovává vnitřní stav aplikace. Do této kategorie spadají objekty typu Player, Shot, Gun.

### View ###

Tato část se stará o zobrazování dat a celé grafické rozhraní. Typicky lze zde najít třídy typu Window, Dialog, ChatPanel.

### Controller ###

Jádro celé aplikace, které celou hru řídí. Controller má jednak za úkol řízení hry, jako např. detekci kolizí, pohyb hráčů, kontroluje zvyšování skóre. Druhým jeho úkolem je síťová komunikace, kdy dochází k odesílání a přijímání dat, přičemž zároveň dochází k tvorbě packetů a při příjmu k jejich parsování a volání metod na modelu. Čímž se dostáváme k jeho poslední úloze - spojuje model s view, tedy předává view informace, že se změnil model, případně přímo sám view říká, co se má v danou chvíli zobrazovat.

## Server - Client ##

V aplikaci je využita ještě jedna architektura, která výrazně ovlivňuje její chování. Jedná se o síťovou architekturu, kdy jeden z hráčů působí ve hře jako server a všichni ostatní jeho spoluhráči se k němu připojují. Celý herní engine běží pouze na serveru, přičemž všem klientům jsou po vyhodnocení pouze zasílány informace, se stalo. Úkolem klientů je tedy pouze server informovat o aktivitách hráče a následně zobrazovat data přijatá od serveru.