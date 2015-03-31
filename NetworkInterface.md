# NetworkInterface #

Tato třída je třídou abstraktní a obsahuje pouze čistě virtuální metody. Potomky této třídy jsou třídy Client a Server, které tak mají zaručeně společné rozhraní a mohou být tedy zapozdřeni do jednoho objektu, se kterým se komunikuje jednotným způsobem.

Toto zapouzdření je zejména důležité pro odesílání zpráv po síti, protože odstiňuje herní logiku od architektury server-klient a usnadňuje tak průběh hry.