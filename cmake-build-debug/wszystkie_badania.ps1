$exe = ".\projekt_algorytmy.exe"
$glowny_folder = "Wyniki_Koncowe"

$n_it = "50"
$p_opt = "3"         # pivot MIDDLE
$e_opt = "1"         # shellOption Knuth
$rozmiar_z_A = "50000"

if (!(Test-Path $glowny_folder)) { New-Item -ItemType Directory $glowny_folder }

function Uruchom-Benchmark($subfolder, $plik, $cmd_args) {
    $path = "$glowny_folder\$subfolder"
    if (!(Test-Path $path)) { New-Item -ItemType Directory -Force -Path $path }
    $res_file = Join-Path $path $plik

    # Bezpieczne rozbicie argumentów na tablicę
    $arg_array = $cmd_args.Split(" ", [System.StringSplitOptions]::RemoveEmptyEntries)
    $arg_array += @("-n", $n_it, "-r", $res_file, "-b")

    # Używamy ${} aby PowerShell nie pomylił dwukropka ze zmienną dyskową
    Write-Host "Runner (n=50) -> ${subfolder} | ${cmd_args}" -ForegroundColor Cyan

    # Wywołanie z tablicą argumentów
    & $exe $arg_array
}

# --- BADANIE A ---
Write-Host "`n--- URUCHAMIAM BADANIE A (Skalowalność) ---" -ForegroundColor Yellow
$algorytmy = "4", "5", "6"
$struktury = "0", "1", "2"
$rozmiary = "10000", "25000", "50000", "100000"

foreach ($a in $algorytmy) {
    foreach ($s in $struktury) {
        foreach ($l in $rozmiary) {
            $cmd = "-a $a -s $s -l $l -d 0 -t 0"
            if ($a -eq "5") { $cmd += " -p $p_opt" }
            if ($a -eq "6") { $cmd += " -e $e_opt" }
            Uruchom-Benchmark "Badanie_A" "wyniki_A.csv" $cmd
        }
    }
}

# --- BADANIE B ---
Write-Host "`n--- URUCHAMIAM BADANIE B (Rozkład danych) ---" -ForegroundColor Yellow
foreach ($s in "0", "1", "2") {
    foreach ($d in "0", "1", "2", "3") {
        Uruchom-Benchmark "Badanie_B" "wyniki_B.csv" "-a 5 -s $s -p $p_opt -l $rozmiar_z_A -d $d -t 0"
    }
}

# --- BADANIE C ---
Write-Host "`n--- URUCHAMIAM BADANIE C (Typy danych) ---" -ForegroundColor Yellow
foreach ($t in "0", "1", "4", "5") {
    Uruchom-Benchmark "Badanie_C" "wyniki_C.csv" "-a 5 -s 0 -p $p_opt -l $rozmiar_z_A -d 0 -t $t"
}

# --- BADANIE OMEGA ---
Write-Host "`n--- URUCHAMIAM BADANIE OMEGA (Struktury) ---" -ForegroundColor Magenta
$struktury_omega = "0", "1", "2", "4", "5"
foreach ($s in $struktury_omega) {
    Uruchom-Benchmark "Badanie_Omega" "wyniki_Omega.csv" "-a 5 -s $s -p $p_opt -l 10000 -d 0 -t 0"
}

Write-Host "--- FINISH ---" -ForegroundColor Green