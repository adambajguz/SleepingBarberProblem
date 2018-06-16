# SleepingBarber-Mutex--and--Semaphores-or-Conditional-Variables

3. Problem �pi�cego fryzjera
Salon fryzjerski sk�ada si� z gabinetu z jednym fotelem oraz z poczekalni zawieraj�cej n krzese�. W danym momencie w gabinecie mo�e by� strzy�ony tylko jeden klient, reszta czeka na wolnych krzes�ach w poczekalni. Fryzjer po sko�czeniu strzy�enia prosi do gabinetu kolejnego klienta, lub ucina sobie drzemk�, je�li poczekalnia jest pusta. Nowy klient budzi fryzjera je�li ten �pi, lub siada na wolne miejsce w poczekalni je�li fryzjer jest zaj�ty. Je�li poczekalnia jest pe�na, to klient nie wchodzi do niej i rezygnuje z wizyty.

Napisz program koordynuj�cy prac� gabinetu. Zsynchronizuj w�tki klient�w i fryzjera:

bez wykorzystania zmiennych warunkowych (tylko mutexy/semafory) [17 p]
wykorzystuj�c zmienne warunkowe (condition variables) [17 p]
Aby m�c obserwowa� dzia�anie programu, ka�demu klientowi przydziel numer. Program powinien wypisywa� komunikaty wed�ug poni�szego przyk�adu:

Res:2 WRomm: 5/10 [in: 4]

Oznacza to, �e dw�ch klient�w zrezygnowa�o z powodu braku miejsc (Res), w poczekalni (WRoom) zaj�tych jest 5 z 10 krzese�, a w gabinecie obs�ugiwany jest klient o numerze 4. Po uruchomieniu programu z parametrem -debug nale�y wypisywa� ca�a kolejka klient�w czekaj�cych, a tak�e lista klient�w, kt�rzy nie dostali si� do gabinetu. Komunikat nale�y wypisywa� w momencie zmiany kt�rejkolwiek z tych warto�ci.

Uwagi dot. sprawozdania:
Rozwi�zania wykorzystuj�ce zmienne warunkowe musz� posiada� kolejk� FIFO dla czekaj�cych w�tk�w.
Prosz� koniecznie zaznaczy� wybran� wersj� projektu (tym samym oczekiwan� ilo�� punkt�w).
Zamie�ci� w sprawozdaniu t� cz�� kod programu, wyr�niaj�c (np. pogrubion� czcionk�) fragmenty korzystaj�ce z mechanizm�w synchronizacji.
Opisa� konkretne przeznaczenie i spos�b wykorzystania ka�dego mechanizmu synchronizacji (semafora, mutexu, zmiennej warunkowej). Mo�na to zrobi� w formie komentarzy do kodu umieszczonych w miejscach, gdzie u�ywany jest kt�ry� z tych mechanizm�w).
Za ka�dy przypadek potencjalnego wy�cigu -3p.