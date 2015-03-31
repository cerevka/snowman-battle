# Vytváření a zpracování paketů #

Pro potřeby aplikace jsme si vytvořili vlastní protokol. Vzhledem k tomu, že po síti musíme přenášet i chatové zprávy, mají naše pakety proměnou délku. Všechny pakety jsou reprezentovány jako pole unsigned char. První 3 byte jsou hlavička a vypadají takto:

0. pole - velikost zprávy v počtu charů <br>
1. pole - odesilatel (server je 0) <br>
2. pole - typ zprávy <br>

Další byty paketu se už liší podle typu (u některých typů se posílá jen samotná hlavička). Celkem máme něco okolo 30 různých typů zpráv (Seznam je uveden v prezentaci).<br>
<br>
V programu se o tyto zprávy starají třídy PacketCreator a PacketParser. PaketCreator, jak již název napovídá, slouží k vytváření paketů, které budou následně odeslány po síti. Tato třída má spoustu slotů, která volají ostatní části aplikace a podle toho se vytváří a posílají pakety. Většinou platí, že jeden slot odpovídá jednomu typu paketu. Takto vypadá několik slotů:<br>
<br>
<br>
<pre><code><br>
    /**<br>
     * Slot, do kterého se posílá, že hráč pustil klávesu pro pohyb<br>
     */<br>
    void stopMove(void);<br>
<br>
    /**<br>
     * Slot pro odeslání hello paketu<br>
     */<br>
    void sendHelloPacket(void);<br>
<br>
    /*********************************************************/<br>
    /* -------------sloty pro výstup enginu hry------------- */<br>
<br>
    /**<br>
     * Slot, do kterého se posílá informace o tom, že je možné odeslat paket enginu hry<br>
     */<br>
    void sendGameEnginePacket(void);<br>
<br>
    /**<br>
     * Slot, do kterého se posílá informace o naspawnování hráče<br>
     * @param playerID id hráče, který se má spawnout<br>
     * @param x x-ová souřadnice místa spawnutí (levý horní roh)<br>
     * @param y y-ová souřadnice místa spawnutí (levý horní roh)<br>
     * @param direction směr, kterým bude hráč otočený<br>
     */<br>
    void spawnPlayer(int playerID, int x, int y, int direction);<br>
<br>
</code></pre>

Naproti tomu třída PacketParser čte a rozpoznává. Podle toho který z paketů přijde, vyemituje správný signál. Pro příklad ukáži několik signálů:<br>
<br>
<pre><code><br>
    /**<br>
     * Signál zničení střely<br>
     * @param shotID id střely, který se má zničit<br>
     */<br>
    void shotDestroyed(int shotID);<br>
<br>
    /**<br>
     * Signál výstřelu hráče (pro odečtení nábojů)<br>
     * @param playerID id hráče, který vystřelil<br>
     */<br>
    void playerShoted(int playerID);<br>
<br>
    /**<br>
     * Signál zvýšení skóre hráče<br>
     * @param playerID id hráče, kterému se zvýšilo skóre<br>
     */<br>
    void playersScoreIncremented(int playerID);<br>
<br>
    /**********************************************************/<br>
    /* -------------------řídící signály--------------------- */<br>
<br>
    /**<br>
     * Signál ukončení hry<br>
     */<br>
    void gameQuited(void);<br>
<br>
</code></pre>