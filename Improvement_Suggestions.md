# Optimierungspotenziale des ursprünglichen Programmentwurfs

In diesem Dokument werden mögliche Optimierungspotenziale für das Programm beschrieben. Die Häkchen zeigen, welche Verbesserungen durchgeführt werden konnten.

##Ursprünglich geforderte Funktionalitäten 
>Spielmodus 1
- [x] **Mauskoordinaten erkennen**: Ein verfehlter Klick soll als solcher erkannt und ausgewertet werden.
- [x] **Strafzeit**: Die Strafzeit soll bei Verfehlen auf die Reaktionszeit addiert werden.
- [ ] **Nichtklicken**: Nach 3 Sekunden, die der Spieler nicht reagiert, soll zum nächsten Bild gewechselt werden und die entsprechende Strafzeit auf die Gesamtzeit addiert werden.

>Spielmodus 2
- [x] **Mauskoordinaten erkennen**: Ein verfehlter Klick soll als solcher erkannt und ausgewertet werden
- [x] **Gesamtzeit**: Die Gesamtzeit soll nach dem Spiel inklusive Strafzeit ausgegeben werden.
- [x] **Strafzeit**: Die Strafzeit soll bei Verfehlen auf die Reaktionszeit addiert werden.
- [ ] **Nichtklicken**: Nach 3 Sekunden, die der Spieler nicht reagiert, soll zum nächsten Bild gewechselt werden und die entsprechende Strafzeit auf die Gesamtzeit addiert werden.
- [ ] **Bestätigung durch Leertaste**: Der Spieler soll seine Eingabe mit der Leertaste bestätigen müssen.

##Sinnvolle Funktionalität
##Spielmodus 2
- [ ] **Klicken verbieten**: Erst nachdem die Box rot geworden ist soll ein Klicken möglich sein (macht nur sinn bei Spielmodus 2)

##Feedback bei beiden Spielmodi
- [x] **Gesamtzeit**: Die Gesamtzeit soll nach dem Spiel, inklusive Strafzeit, ausgegeben werden.
- [x] **Anzeige durchschnittliche Reaktionszeit**: Die durchschnittliche Reaktionszeit (also ohne Strafzeit) soll, errechnet und ausgegeben werden.
- [x] **Anzeige beste 3 Ergebnisse**: Von den 3 schnellsten Reaktionen sollen die Reaktionszeiten nach dem Spiel ausgegeben werden.
- [ ] **Anzeige der Top 3 mit Bildnummer**: Bei den Top 3 schnellsten Reaktionszeiten soll die jeweilige Bildnummer dabei stehen.

##Wartbarkeit
- [ ] **Mehrere Vorraussetzungen auslagern** Bsp Klick innerhalb einer Box nur noch auf true oder false setzen