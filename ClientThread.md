# ClientThread #

Tato třída je potomkem QThread a její význam je hlavně v naslouchání příchozích dat ze sítě ve vlastním vlákně nezávisle na zbytku aplikace. Třída je napsána tak, aby se dala používat jak serverem i klientem.

Vlánko při svém spuštění zapíná smyčku událostí a dále již pouze reaguje na signály šířené aplikací a emituje signály o nových zprávách.

## Server ##

Server si pro každého klienta spouští nové vlákno, čím zajišťuje pro každého klienta nezávislou komunikaci na ostatních klientech.

## Client ##

Na rozdíl u serveru zde vzniká vlákno pouze v jedné instanci a naslouchá zprávám přicházejícím od serveru.