# Network #

Třída poskytující jednotné rozhraní pro komunikaci klienta a serveru. Vše funguje za pomoci třídy NetworkInterface, do které si Network zapouzdřuje třídy Server a Client.

Ve výsledku jsou třídy Server a Client používany přímo pouze při připojování. Když je hra odstartována, komunikuje se již pouze prostřednictvím třídy Network