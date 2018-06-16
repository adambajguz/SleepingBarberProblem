# SleepingBarber-Mutex--and--Semaphores-or-Conditional-Variables

3. Problem œpi¹cego fryzjera
Salon fryzjerski sk³ada siê z gabinetu z jednym fotelem oraz z poczekalni zawieraj¹cej n krzese³. W danym momencie w gabinecie mo¿e byæ strzy¿ony tylko jeden klient, reszta czeka na wolnych krzes³ach w poczekalni. Fryzjer po skoñczeniu strzy¿enia prosi do gabinetu kolejnego klienta, lub ucina sobie drzemkê, jeœli poczekalnia jest pusta. Nowy klient budzi fryzjera jeœli ten œpi, lub siada na wolne miejsce w poczekalni jeœli fryzjer jest zajêty. Jeœli poczekalnia jest pe³na, to klient nie wchodzi do niej i rezygnuje z wizyty.

Napisz program koordynuj¹cy pracê gabinetu. Zsynchronizuj w¹tki klientów i fryzjera:

bez wykorzystania zmiennych warunkowych (tylko mutexy/semafory) [17 p]
wykorzystuj¹c zmienne warunkowe (condition variables) [17 p]
Aby móc obserwowaæ dzia³anie programu, ka¿demu klientowi przydziel numer. Program powinien wypisywaæ komunikaty wed³ug poni¿szego przyk³adu:

Res:2 WRomm: 5/10 [in: 4]

Oznacza to, ¿e dwóch klientów zrezygnowa³o z powodu braku miejsc (Res), w poczekalni (WRoom) zajêtych jest 5 z 10 krzese³, a w gabinecie obs³ugiwany jest klient o numerze 4. Po uruchomieniu programu z parametrem -debug nale¿y wypisywaæ ca³a kolejka klientów czekaj¹cych, a tak¿e lista klientów, którzy nie dostali siê do gabinetu. Komunikat nale¿y wypisywaæ w momencie zmiany którejkolwiek z tych wartoœci.

Uwagi dot. sprawozdania:
Rozwi¹zania wykorzystuj¹ce zmienne warunkowe musz¹ posiadaæ kolejkê FIFO dla czekaj¹cych w¹tków.
Proszê koniecznie zaznaczyæ wybran¹ wersjê projektu (tym samym oczekiwan¹ iloœæ punktów).
Zamieœciæ w sprawozdaniu t¹ czêœæ kod programu, wyró¿niaj¹c (np. pogrubion¹ czcionk¹) fragmenty korzystaj¹ce z mechanizmów synchronizacji.
Opisaæ konkretne przeznaczenie i sposób wykorzystania ka¿dego mechanizmu synchronizacji (semafora, mutexu, zmiennej warunkowej). Mo¿na to zrobiæ w formie komentarzy do kodu umieszczonych w miejscach, gdzie u¿ywany jest któryœ z tych mechanizmów).
Za ka¿dy przypadek potencjalnego wyœcigu -3p.