# Vize #

## Základní specifikace ##

  * klon populární hry [Bulánci](http://www.bulanci.sleepteam.com)
  * 2D real-time střílečka pro více hráčů
  * jeden z hráčů bude sloužit jako server, ostatní se na něj budou připojovat
  * podpora chatu mezi hráči
  * automatická obnova spojení při výpadku
  * identifikace lagů bez ukončení celé hry, dočasné postavení hráče mimo hru (duch)
  * jazyk C++ s grafickou knihovnou [Qt](http://qt.nokia.com/) v Linuxu

## Rozšiřující specifikace ##

  * možnost změny ovládání
  * přestřelitelné a nepřestřestřelitelné překážky
    * díry, voda...
    * zdi, bedny...
    * balíčky zbraní
  * více zbraní - základ tři
    * Sněhopistol
    * Sněhovnice
    * Sněhopal
  * základní zbraní bude pistole - bez omezení střeliva
    * ostatní zbraně se budou objevovat ve formě "balíčku", které budou hráči moci sbírat ovšem s omezenou municí

## Bonusové specifikace ##

_(aneb když zbude čas)_

  * hudba na pozadí
  * zvuky na popředí
  * granáty a miny


## Fáze vývoje ##
  1. Návrh a vize
  1. Síťová komunikace
  1. Herní engine
  1. Testování