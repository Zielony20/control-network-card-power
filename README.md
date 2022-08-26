Temat : Narzędzie sterujące mocą sygnału karty sieciowej

Program przygotowałem pod moją domową kartę sieciową, która jest w stanie osiągnąć 20dBm.
Makro MAXDBM odpowiada tej wartości. Jeżeli chcemy osiągnąć większą moc należy tę wartość zwiększyć.
Program dostosuje moc sygnału karty do procentowej wartości wskazanej przez użytkownika inkrementując lub dekrementując stopniowo moc sygnału dla bezpieczeństwa karty.
Wykorzystana została biblioteka wireless.h
Zmiany można obserwować również pod polecniem "watch iwconfig". 

Zawartość plików:
main.c - kod programu

Kompilacja:
gcc -Wall main.c -o ./main

Uruchomienie (wymagane uprawnienia root'a)
./main [nazwa karty sieciowej] [0-100]
