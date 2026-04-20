$rozmiar = "25000"
$wyniki = "wyniki_alfa.csv"
$iteracje = "50"

Write-Host "--- ROZPOCZYNAM BADANIE ALFA ---" -ForegroundColor Cyan

if (Test-Path $wyniki) { Remove-Item $wyniki }

foreach ($p in "0", "1", "2", "3") {
    Write-Host "Testuje QuickSort: Pivot $p"

    .\projekt_algorytmy.exe -b -a 5 -s 0 -p $p -t 0 -d 0 -l $rozmiar -n $iteracje -r $wyniki
}

foreach ($e in "0", "1") {
    Write-Host "Testuje ShellSort: Opcja $e"

    .\projekt_algorytmy.exe -b -a 6 -s 0 -e $e -t 0 -d 0 -l $rozmiar -n $iteracje -r $wyniki
}

Write-Host "--- BADANIE ZAKOŃCZONE ---" -ForegroundColor Green