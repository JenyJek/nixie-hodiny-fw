<H2>úvodem</H2>
Jmenuji se Jan Kerber a tohle je moje maturitní práce. Krátce vám představím, proč jsem si vybral zrovna tento projekt:
# 1. Od nápadu k realizaci

## 1.1 Volba projektu: Proč právě hardware?

V éře, kdy se většina technologického pokroku odehrává v abstraktní rovině softwaru a virtuálních simulací, jsem se rozhodl vydat cestou **hardwarového projektu**. Hlavní motivací byla touha vytvořit něco hmatatelného – zařízení, které propojuje precizní elektroniku, mikrokontroléry a design. Hardware neodpouští chyby a navíc je tu onen reálný prvek světa, který není třeba u softwarového vývoje v dokonalém, simulovaném prostředí brát v potaz, což z něj činí vynikající výzvu.
## 1.2 Proč právě hodiny?
Hodiny naprosto dokonalým projektem pro digitrony. Představují ideální užití zobrazování rovnováhu mezi **užitnou hodnotou** a **technickou komplexností**. Zatímco jejich základní funkce je prostá, dosažení přesnosti, spolehlivého zobrazení a dlouhodobé stability vyžaduje promyšlený přístup k návrhu. Jsou to zařízení, se kterými uživatel interaguje každý den, a narozdíl od dalších zařízení běží klidně i několik let v kuse - je tedy třeba zajistit bezchybnou funkci a brát v potaz přetečení čítačů, což se u krátce běžících zařízení nemusí řešit.
## 1.3 Kouzlo technologie „zlatých sedmdesátek“
Otázka, proč v roce 2026 stavět hodiny s technologií, která byla na vrcholu v roce 1969, má pro mě dvě roviny:
### 1.3.1 Estetika a unikátnost: 
Digitrony v sobě nesou specifické jakési  jakési specifické kouzlo, kterému moderní LED nebo LCD displeje nemohou konkurovat. Hřejivý, jasně oranžový výboj neonu v kombinaci s prostorově naskládanými katodami vytváří unikátní vizuální hloubku. Každá číslice má svůj vlastní charakter. Pro mě jako konstruktéra je digitron symbolem doby, kdy i součástky měly svou duši.
### 1.3.2 Součástky mám doma:
Významným impulsem pro tento projekt byla skutečnost, že jsem již vlastnil sadu těchto historických součástek. Vzhledem k tomu, že se digitrony již desítky let nevyrábí a jejich cena na trhu sběratelů strmě roste, považoval jsem za smysluplné vdechnout těmto konkrétním kusům život v moderním zařízení. Namísto toho, aby zůstaly zapomenuty v krabici, stanou se srdcem funkčního přístroje, který propojuje historii s moderní technologií.
## 1.4 Digitron: Princip a konstrukce
Hlavní premisa těchto hodin jsou již zmíněné **digitron**y (v anglické literatuře známý jako *Nixie tube*, nebo znaková výbojka). Jedná se o speciální typ výbojky se studenou katodou, plněnou směsí vzácných plynů za nízkého tlaku. Z fyzikálního hlediska lze digitron definovat jako více doutnavek v jedné obálce se společnou anodou a deseti samostatnými katodami.
### 1.4.1 Vnitřní uspořádání a materiály
Digitron je skleněná baňka, v níž je umístěno celkem 11 elektrod:
jedna **Anoda**, která má podobu jemné kovové mřížky (klece), která obklopuje celý systém katod a zajišťuje rovnoměrné elektrické pole. Pro vyrovnanější elektrické pole se umisťuje jedna anodová mřížka doprostřed. Zajímavost je, že pro usnadnění výroby se u našich, československých digitronů často nepoužívá mřížka v pravém slova smyslu, ale obrácená elektroda ve tvaru osmičky. Má to mnoho výhod. Za prvé je ušetřeno na výrobních nákladech, neboť se nemusí vyrábět další tenká mřížka, a za druhé je vylepšena i viditelnost - mřížka by blokovala víc světla, než tenká číslice.
Všechny ostatní elektrody představují **Katody**. Jsou tvořeny deseti tenkými plíšky vytvarovanými do podoby úzkých číslic 0 až 9. Tyto číslice jsou naskládány v těsném závěsu za sebou.

Vnitřní prostor je vyplněn směsí plynů, kde dominantní složku tvoří **neon**. Pro zlepšení elektrických vlastností, zejména pro snížení zapalovacího napětí, se do směsi přidává malé množství radioaktivních izotopů (např. krypton-85). Dále se přidává **rtuť**, která omezuje rozprašování materiálu katod a prodlužuje tak životnost součástky. Právě příměs rtuti způsobuje charakteristický modrý nádech výboje, který se v praxi často eliminuje použitím vnějšího červeného filtru pro zvýšení kontrastu a čitelnosti, jež je nanesen na vnější povrch skleněné schránky. 
### 1.4.2  Fyzikální princip zobrazení
Zobrazení konkrétní číslice je založeno na vzniku **doutnavého výboje**. Po přivedení dostatečného napětí mezi anodu a vybranou katodu dochází k ionizaci plynu. Volné elektrony urychlované k anodě kolidují s atomy plynů, čímž dochází k jejich excitaci. Při následném návratu elektronů na nižší energetickou hladinu dochází k vyzáření fotonů v definovaném spektru - pro majoritní složku neon je to typická, oranžová barva. Jelikož výboj obklopuje přímo povrch aktivované katody, oko pozorovatele vnímá zářící obrys konkrétní číslice.
## 1.5 Výhody a specifika provozu
Hlavní předností digitronů oproti modernějším segmentovým (LED) nebo maticovým displejům je **typografická věrnost**. Číslice nejsou složeny z úseček, ale mají přirozený tvar a není tedy nutné odhadovat, co číslice představuje. Tím je zajištěna vynikající čitelnost a estetická hodnota.
### 1.5.1 Technická úskalí a řízení
Navzdory vizuálním výhodám s sebou digitrony nesou několik technických komplikací:
- **Vysoké napětí:** Pro zapálení výboje je nutné ionizační napětí (typicky v rozmezí 170–190V). V mé konstrukci je tento požadavek řešen pomocí boost měniče vysokého napětí (HV zdroje).
- **účinnost:** Ačkoliv je výboj ve zobrazovači studený, k jeho správnému zapálení a udržování je zapotřebí proud okolo $4 ma$. Dle vztahu pro výkon je $P = UI$, tedy $P=175V\cdot0.004A=0.7W=700mW$ Pro šestero digitronů je potom celkový odběr $4,2 W$. bereme-li v potaz i účinnost zdroje vysokého napětí, výkonovou ztrátu na omezovacím odporu a samotný odběr řídící elektroniky, vyšplhá se spotřeba na $\approx6.7W$. 
- **Způsob řízení:** Pro spínání jednotlivých katod nelze použít běžné logické obvody pracující s nízkým napětím. Jsou zapotřebí buď vysokonapěťové tranzistory, nebo specializované integrované obvody určené přímo pro řízení doutnavkových zobrazovačů (např. sovětský dekodér *К155ИД1*, náš, český ekvivalent *MH74141* nebo západní *74SN141*).
- **Otrava katod (Sputtering):** Pokud je dlouhodobě zobrazována pouze jedna číslice, dochází k usazování odprášeného materiálu z aktivní katody na ty neaktivní. To vede k postupné degradaci čitelnosti. tomuto jevu lze relativně jednoduše předejít, a to snahou o rovnoměrné používání všech číslic.
## 1.6 Historický kontext a dostupnost
Digitrony dosáhly vrcholu své popularity v 60. a 70. letech 20. století, kdy byly hojně využívány v měřicích přístrojích a prvních kalkulačkách. S nástupem fluorescenčních (VFD) displejů a pozdější LED technologie byly zcela nahrazeny a výroba koncem 20. století ukončena. V současnosti se jedná o vzácné, leč velice žádané součástky, jejichž cena na trhu neustále roste z důvodu omezených zásob a vysoké poptávky v komunitě radioamatérů a designérů. Obdobná situace je i se specializovanými řídícími obvody, jež se rovněž dávno nevyrábí, a jak praví zákony schválnosti, čipy zakoupeny na bazarech jsou často "nakřáplé" - degradované a na konci své životnosti.
## 1.7 Požadavky na zařízení (Design requirements)
Na základě výše zmíněného jsem si stanovil následující technické a designové cíle:
- **Vizuál:** Design musí nechat vyniknout krásu digitronů, zbytek elektroniky by měl být v krabici nebo vkusně doplňovat retro vzhled.
- **Bezpečnost a spolehlivost:** Jelikož digitrony vyžadují k provozu vysoké napětí ($170V$), prioritou je galvanické oddělení všech částí od těla. Proto bude vysokonapěťový zdroj řešen diskrétně od hlavního mikrokontroléru.
- **Dlouhověkost:** Implementace funkcí pro ochranu digitronů. To bude řešeno automatickým vypínáním a zapínáním displeje pomocí radaru a pravidelné „protáčení“ všech číslic pro zamezení a prevenci otravy katod.
- **Moderní řízení:** I když je zobrazovací metoda historická, srdcem hodin bude relativně moderní mikrokontrolér doplněný modulem reálného času s externím backup napájením DS3231, zajišťujícím přesné měření času.
- **Chytré řízení displaye:** Jelikož je řídících čipů málo, rozhodl jsem se pro tříkrokový multiplex pomocí trojice high-side tranzistorů a dvojice MH74141.
- **Jednoduché ovládání:** To je základem všech zařízení, která člověk během jejich používání nechce rozmlátit. V mém případě půjde o jedno, dotykové tlačítko na vrchní straně hodin doplněné o zvukovou, "haptickou" odezvu.
- **Efektní zvuková signalizace:**  Jak už bylo zmíněno, hodiny budou mít zvukovou odezvu. Nerad bych ale uživateli zavinil krvácení uší, kdybych používal jednoduchý piezoelektrický pípák, a tak bude zvuková signalizace řešena pomocí reproduktorku přehrávájícího jednoduché melodie.
- **Funkce:** Chci i další funkce mimo zobrazování hodin. Mezi ně bude patřit budík, kalendář (jednoduché zobrazení data), zobrazení orientační teploty apod.
# 2. Stavba
## 2.1. Vysokonapěťový napájecí zdroj (HV Source)
Pro provoz digitronů je nezbytné zajistit stejnosměrné napětí v rozsahu **170–190 V**. Vzhledem k tomu, že celé zařízení je napájeno bezpečným malým napětím (12 V DC), bylo nutné do zapojení integrovat zvyšující měnič (**Boost Converter**).
### 2.1.1. Princip zvyšujícího měniče (Boost Converter)
Zvyšující měnič je typ spínaného zdroje, který využívá schopnosti cívky (indukčnosti) akumulovat energii v magnetickém poli. Princip lze rozdělit do dvou fází:
1. **Fáze sepnutí:** Spínací prvek (MOSFET) se sepne, proud protéká cívkou a dochází k akumulaci energie.
2. **Fáze rozepnutí:** Spínací prvek se rozpojí. Jelikož cívka brání prudké změně proudu, indukuje se na ní napětí opačné polarity, které se sčítá s napětím vstupního zdroje. Tato energie je přes diodu přenesena do výstupního kondenzátoru.
### 2.1.2. Řídicí obvod MC34063
Jako srdce zdroje byl zvolen integrovaný obvod **MC34063**. Jedná se o univerzální monolitický řídicí obvod pro spínané regulátory, který obsahuje:

- Teplotně kompenzovanou referenci (1,25 V).
- Oscilátor s nastavitelnou frekvencí pomocí externího kondenzátoru.
- Komparátor a obvod pro omezení špičkového proudu.
- Výstupní spínací tranzistor (v mém zapojení slouží jako budič externího výkonového MOSFETu).

Hlavním důvodem volby tohoto čipu je jeho nízká cena, široká dostupnost, předchozí zkušenost, jednoduchost zapojení, jednoduchost oživení a schopnost pracovat v širokém rozsahu vstupních napětí. (jedinými nevýhodami jsou nižší účinnost a vysoký věk integrovaného obvodu (na Mouser Electronic má status NRND-Not Recommended for New Design)). Vzhledem k vysokému výstupnímu napětí (170 V) je v zapojení použit externí MOSFET, který jsem vytěžil z vyřazené televize, který zvládne vysoké napěťové namáhání, na které není vnitřní tranzistor čipu dimenzován.
### 2.1.3. Výpočty a dimenzování komponent
Návrh zdroje vychází ze základních rovnic pro obvod MC34063 uvedených v datasheetu, dokumentaci výrobce.
#### 2.1.3.1. Výstupní napětí
Výstupní napětí $V_{out}$ je určeno poměrem rezistorů $R_1$ and $R_2$ v napěťovém děliči zpětné vazby. Referenční napětí čipu $V_{ref}$ je 1,25 V.
$$V_{out} = 1,25 \cdot \left(1 + \frac{R_2}{R_1}\right)$$

Pro dosažení napětí **170 V** byly zvoleny hodnoty rezistorů $R_1 = 10\,k\Omega$ a $R_2 \approx 1,35\,M\Omega$. Realizováno to je sériovým zapojením obou rezistorů do děliče, doplněným o odrušovací kondenzátor.
#### 2.1.3.2. Pracovní frekvence
Pracovní frekvence oscilátoru $f_{osc}$ je určena kapacitou kondenzátoru $C_T$ připojeného k pinu 3. Pro stabilitu a eliminaci slyšitelného pískání byla zvolena frekvence nad hranicí lidského sluchu (typicky 30–50 kHz).
$$C_T = 4 \cdot 10^{-5} \cdot t_{on}$$
_(Kde $t_{on}$ je doba sepnutí spínače)._

*pozn. pískání není možné 100% eliminovat tím, že vybereme vyšší než slyšitelnou frekvenci. Proud protékající cívkou vytváří proměnné magnetické pole, které způsobuje mikroskopické deformace jádra a vinutí (jev zvaný magnetostrikce). Pokud se vlivem regulační smyčky v proudu objeví složky s nižší frekvencí, cívka začne fungovat jako malý reproduktor. Obvod MC34063 pracuje na principu hysterezního nebo PWM řízení. Při nízkém odběru nebo vlivem nestability v regulační smyčce může docházet k tzv. „vynechávání pulzů“ (Pulse Skipping). Tím vznikají shluky pulzů, jejichž opakovací frekvence (obálka) již spadá do slyšitelného pásma. Za druhé se během funkce mění střída, která superponuje nízkofrekvenční, slyšitelnou složku*
#### 2.1.3.3. Špičkový proud a indukčnost
Aby nedošlo k nasycení jádra cívky, je nutné vypočítat maximální proud $I_{pk}$. Ten je omezen rezistorem $R_{sc}$ (current sense). Pokud úbytek na tomto rezistoru překročí 0,3 V, čip omezí další nárůst proudu.
$$R_{sc} = \frac{0,3}{I_{pk}}$$
Rezistor $R_{sc}​$ (Current Sense) standardně slouží k monitorování špičkového proudu protékajícího cívkou a spínacím tranzistorem. Pokud úbytek napětí na tomto rezistoru překročí hranici **0,3 V**, vnitřní logika obvodu MC34063 okamžitě ukončí probíhající impulz, čímž chrání komponenty před nasycením a tepelným zničením.

V mém zapojení byl tento rezistor nahrazen **propojkou (0Ω)**. K tomuto kroku jsem přistoupil z několika důvodů:
1. **Eliminace předčasného vypínání:** Při generování vysokého napětí z nízkého vstupního napětí vykazuje měnič vysokou střídu (duty cycle) a špičkové proudy mohou krátkodobě dosahovat hodnot, které by standardní $R_{sc}$​ vyhodnotil jako chybové. To by vedlo k poklesu výstupního napětí a nestabilitě jasu digitronů.
2. **Optimalizace účinnosti:** Každý rezistor v hlavní proudové cestě představuje energetickou ztrátu ve formě tepla. Odstraněním $R_{sc}​$ se mírně zvýšila celková účinnost měniče a zjednodušila cesta proudu mezi zdrojem a induktorem.
3. **Robustnost externího spínače:** Jelikož nepoužívám vnitřní tranzistor obvodu MC34063, ale výkonný externí MOSFET (dimenzovaný na mnohem vyšší proudy, než jaké reálně v obvodu nastávají), je riziko jeho poškození špičkovým proudem minimální.

**Poznámka k bezpečnosti:** Absence $R_{sc}$​ znamená, že zdroj má značně omezenou ochranu proti tvrdému zkratu na výstupu. Vzhledem k charakteru zařízení (stacionární hodiny v uzavřeném pouzdře) a použití jištěného externího napájecího adaptéru je toto riziko akceptovatelné a v praxi vyvážené vyšší stabilitou vysokonapěťové části.
#### 2.1.3.4. Výpočet minimální indukčnosti cívky
Indukčnost cívky $L$ musí být dostatečně vysoká, aby v době sepnutí spínače akumulovala potřebnou energii a zároveň aby proud cívkou nepřekročil maximální povolenou hodnotu. Pro výpočet minimální indukčnosti $L_{min}$​ u obvodu MC34063 v režimu Boost se používá vztah:
$$L_{min}​=\frac{V_{in(min)}​−V_{sat}​​}{I_{pk(switch)}}⋅t_{on(max)}​$$
Kde:
- $V_{in(min)}​$ je minimální vstupní napětí (např. 9 V).
- $V_{sat}​$ je napěťový úbytek na spínacím prvku (u externího MOSFETu velmi malý, cca 0,1–0,5 V).
- $I_{pk(switch)​}$ je špičkový proud spínačem.
- $t_{on(max)}​$ je maximální doba sepnutí vypočtená z pracovní frekvence a střídy.

Pro zvolenou pracovní frekvenci kolem **40 kHz** a požadovaný výstupní výkon (proud pro 6 digitronů cca 15–20 mA) vychází teoretická hodnota indukčnosti v řádech stovek µH. Zvolená hodnota **330 µH** představuje ideální kompromis:

1. **Dostatečná rezerva:** Zajišťuje, že měnič pracuje v optimálním režimu bez rizika nasycení jádra při špičkových odběrech.
2. **Proudové zvlnění:** Vyšší indukčnost snižuje zvlnění proudu (ripple current), což vede k nižšímu zahřívání výstupního kondenzátoru a delší životnosti celého zdroje.
3. **Fyzická velikost:** Cívka s touto hodnotou je stále kompaktní a vhodná pro montáž na plošný spoj hodin.

#### 2.1.3.5. Schéma
Po výpočtu a návrhu komponent, jejich naleznutí v tzv. nekonečných kyblících součástek (můj způsob jejich uložení, tj. 30L kýbl, ve kterým jsou naházeny všechny cívky, další kde mám kondenzátory,  další s integrovanými obvody,mosfety a tranzistory) jsem nakreslil toto schéma v KiCad EDA.

![[Schema_34063.png]]
<center>obr. 1 - schema HV zdroje</center>



### 2.1.4. Účinnost a tepelné ztráty
Při návrhu byl kladen důraz na minimalizaci tepelných ztrát. Ty vznikají především:
- **Na spínacím MOSFETu:** Díky nízkému odporu v sepnutém stavu ($R_{DS(on)}$) je zahřívání minimální.
- **Na diodě:** Musí být použita ultrarychlá dioda (např. UF4007) s krátkou dobou zotavení ($t_{rr}$), aby se zamezilo ztrátám při vysokých frekvencích.
- **Na cívce:** Musí mít dostatečně dimenzovaný proud a nízký ohmický odpor vinutí.
- **Na řídícím čipu:** Bohužel dáno věkem, nelze zamezit.
## 2.2. Metoda řízení: Multiplexní režim
Vzhledem k tomu, že hodiny obsahují šestici digitronů a každý z nich má 10 katod, bylo by při statickém řízení zapotřebí 60 spínacích cest pro katody a 6 pro anody. To by vedlo k extrémně vysokému počtu potřebných výstupů mikrokontroléru a složitosti plošného spoje. Proto byla zvolena metoda **časového multiplexu**.

### 2.2.1. Princip multiplexu a Persistence vidění (POV)
Multiplexní řízení spočívá v rychlém přepínání mezi jednotlivými digitrony. V každém okamžiku svítí pouze vybraná část displeje, ale díky setrvačnosti lidského oka (**Persistence of Vision**) vnímá uživatel obraz jako spojitý a stálý. Aby nedocházelo k viditelnému blikání, musí být obnovovací frekvence celého cyklu vyšší než 50Hz a pokud možno, konzistentní.

### 2.2.2. Zapojení s budiči MH74141
Srdcem řízení katod jsou dva integrované obvody **MH74141** (vyráběné kdysi národním podnikem Tesla). Jedná se o BCD dekodéry na 1 z 10, které jsou specificky navrženy pro spínání vysokonapěťových studených katod.
- **Vstup:** 4bitový BCD kód (binárně kódovaná dekadická číslice).
- **Výstup:** 10 výstupů s otevřeným kolektorem, které vydrží napětí nad 100V (zbytkové napětí při neaktivním výboji).

Použití dvou obvodů namísto jednoho umožňuje rozdělit hodiny na tři nezávisle řízené sekce, čímž se zvyšuje **střída (duty cycle)** a tím i jas digitronů. Sekce jsou zapojeny v konfiguraci 1-2-3-1-3-2, aby se zamezilo vizuálnímu klamu, že číslice někam ujíždějí.
![[Schema_MH74141.png]]<center>obr.2 - low-side HV spínače v čipu MH74141</center>


### 2.2.3. Anodové spínače (High-Side Switching)
Protože digitron vyžaduje pro zapálení kladné napětí na anodě, je nutné použít vysokonapěťové spínače schopné pracovat s potenciálem 170V. Jelikož mikrokontrolér pracuje s napětím 5V, je zapojení realizováno jako 3× vysokonapěťový PNP spínač a jeho řídící NPN s tranzistory **MPSA42** (NPN) a **MPSA92** (PNP).

**Funkce spínače:**
1. Mikrokontrolér přivede logickou jedničku na bázi tranzistoru **MPSA42**.
2. Tento tranzistor se saturuje (sepne) a stáhne bázi výkonového tranzistoru **MPSA92** k zemi (přes omezovací odpor).
3. Tranzistor **MPSA92** se otevře a propojí zdroj vysokého napětí (170V) s anodou příslušné dvojice digitronů.

Toto kaskádní zapojení bezpečně odděluje nízkonapěťovou logiku od vysokého napětí zdroje. Spínače obsluhují dvojice digitronů v kombinaci se dvěma dekodéry MH74141, což vytváří matici 2×3=6 zobrazovaných pozic.

![[Schema_high_HV.png]]
<center>obr.3 - High-side HV spínač</center>
### 2.2.4. Časování a střída
Klíčovým parametrem je doba, po kterou je digitron aktivní ($t_{on}$​). Pokud máme 3 fáze multiplexu, střída pro jeden digitron je:
$$D=31​≈33,3\%$$
Tento poměr je dostatečný pro dosažení vysokého jasu bez nutnosti přetěžovat katody nadměrným špičkovým proudem. V řídicím softwaru bylo nutné implementovat tzv. **Blanking time** – krátkou prodlevu mezi vypnutím jednoho spínače a zapnutím druhého. Tím se zamezí jevu zvanému „ghosting“ (prosvítání číslice z předchozího kroku na další pozici).

## 2.3. Řídicí mikrokontrolér a softwarový multiplex
Srdcem celého systému je osmibitový mikrokontrolér **ATmega328P** (architektura AVR). Tento čip byl zvolen pro svou vysokou spolehlivost, dostatečný počet I/O pinů, širokou podporu vývojových nástrojů a hlavně proto, že jsem s ním detailněji pracoval v minulosti. Mikrokontrolér zajišťuje nejen veškerou logiku, ale především precizní časování multiplexního cyklu.

![[Schema_ATMega328P-AU.png]]
<center>obr. 4 - zapojení ATMega328P-AU desky a popis registrů PORT</center>
### 2.3.1. Konfigurace časovače Timer1
Aby mohl multiplex probíhat precizně a deterministicky, byla provedena přímá konfigurace 16bitového časovače **Timer1**. Nastavení probíhá zápisem do kontrolních registrů (TCCR – Timer Counter Control Register) během inicializace systému.

#### 2.3.1.1. nastavení a inicializace
Při konfiguraci časovače je nezbytné zajistit, aby se interrupt nespustil a aby rozpracované nastavení nebylo přerušeno jinou událostí. Toho je docíleno dočasným zakázáním globálních přerušení pomocí instrukce `noInterrupts()`.

Následně jsou registry `TCCR1A` a `TCCR1B` vynulovány, čímž se časovač uvede do definovaného výchozího stavu. Čítač `TCNT1` je rovněž vynulován pro synchronizaci startu.

#### 2.3.1.2. Volba režimu CTC a výpočet frekvence
Pro účely multiplexu byl zvolen režim **CTC (Clear Timer on Compare Match)**. V tomto režimu čítač neustále počítá směrem nahoru a v momentě, kdy jeho hodnota dosáhne hodnoty uložené v registru `OCR1A`, dojde k vyvolání přerušení a okamžitému vynulování čítače.

Hodnota registru `OCR1A` je vypočtena podle vztahu:
$$OCR1A=\frac{f_{clk\_io}​​}{N⋅f_{target}​}−1$$
Kde:
- $f_{clk_io}$​ je frekvence oscilátoru (16MHz).
- $N$ je hodnota děličky (Prescaler), v mém případě nastavená na **8** (bit `CS11`).
- $f_{target​}$ je požadovaná frekvence „tiků“ časovače.

Při zvolené hodnotě **249** získáváme frekvenci přerušení:

$$\frac{16000000}{8⋅(249+1)}​=8000Hz$$
#### 2.3.1.3. Tabulka nastavení registrů
Pro přehlednost jsou použité bity a jejich funkce shrnuty v následující tabulce:

|Registr|Bit|Funkce|Význam|
|---|---|---|---|
|**TCCR1B**|`WGM12`|CTC Mode|Časovač se nuluje při shodě s OCR1A.|
|**TCCR1B**|`CS11`|Prescaler 8|Hodiny procesoru jsou děleny osmi.|
|**TIMSK1**|`OCIE1A`|Interrupt Enable|Povolení vyvolání ISR při shodě (Compare Match).|
*TCCR = Timer/Counter Control Register, TIMSK = Timer/counter Interrupt MaSK register, WGM**12** = Waveform Generation Mode **1** bit **2**, OCIE1A = Output Compare Interrupt Enable timer **1 A** (trigger volá TIMER**1**_COMP**A**_vect)*

Po dokončení konfigurace jsou globální přerušení opět povolena funkcí `interrupts()`, čímž se spustí samotný proces multiplexního zobrazení na pozadí hlavní smyčky programu.
### 2.3.2. Role Timeru a přerušení (ISR)

Pro zajištění stabilního obrazu bez blikání je kritické, aby k přepínání digitronů docházelo v přesně definovaných intervalech, nezávisle na tom, jaké další operace právě probíhají v hlavní programové smyčce. K tomuto účelu byl využit interní **Timer/Counter1**.

Timer je nakonfigurován tak, aby při dosažení určité hodnoty (režim CTC – Clear Timer on Compare Match) vyvolal přerušení (**ISR – Interrupt Service Routine**).

### 2.3.3. Logika obsluhy multiplexu v ISR

Rutina přerušení provádí cyklickou obsluhu zobrazení v následujících krocích:

1. **Zhasnutí (Blanking):** Vypnutí aktuálně sepnutého anodového spínače (MPSA92). Tím se předchází jevu „ghosting“, kdy by zbytkový náboj mohl způsobit prosvítání předchozí číslice na nové pozici.
2. **Změna dat:** Na výstupní porty, ke kterým jsou připojeny budiče **MH74141**, jsou odeslána BCD data odpovídající aktuální pozici v multiplexu. Jelikož jsou použity dva budiče, odesílají se data pro dvě číslice současně.
3. **Sepnutí anody:** Aktivace příslušného anodového spínače pro novou dvojici digitronů.
4. **Inkrementace indexu:** Posun ukazatele na další pozici v cyklu (0 → 1 → 2 → 0).

Díky tomu, že tento proces probíhá přednostně od hlavní smyčky (MCU je schopen přerušit právě probíhající instrukci, provést ISR a vrátit se bez ztráty kytičky), je jas displeje naprosto konstantní a nedochází k jeho ovlivnění jinými softwarovými procesy.
### 2.3.4. Výpočet obnovovací frekvence

Aby lidské oko nevnímalo blikání, musí být celková frekvence obnovy displeje $f_{disp}$​ minimálně 50 Hz. Protože multiplexní cyklus se v mém zapojení skládá ze tří fází (3 anodové spínače), musí být frekvence volání přerušení $f_{ISR}$​ trojnásobná:

$$f_{ISR}​>f_{disp}​⋅n\to50⋅3\to f_{ISR}>150Hz$$

### 2.3.5. Detailní implementace obsluhy přerušení (ISR)

Rutina přerušení `ISR(TIMER1_COMPA_vect)` je navržena jako stavový automat se dvěma hlavními fázemi: **Blanking** (mrtvý čas) a **On-time** (aktivní zobrazení). Toto rozdělení je voleno kvůli eliminaci parazitních výbojů (ghostingu) a zajištění stability dekodérů.

#### 2.3.5.1. Fáze Blanking (Dead-time)

V této fázi jsou všechny anody i katody odpojeny. Účelem je nechat plyn v digitronu zcela deionizovat předtím, než se zapne další číslice.

- **Vypnutí anod:** Pomocí vynulování bitů 1, 2 a 3 na portu C (zde jsou připojeny anodové spínače). pomocí `PORTC &= ~0x07`. Dochází k okamžitému odpojení všech tří anodových spínačů.
- **Deaktivace dekodérů:** Na vstupy obou obvodů MH74141 je odeslána hodnota `0x0F` (binárně `1111`). Protože tyto dekodéry pracují s BCD kódem 0–9, hodnota 15 leží mimo definovaný rozsah, což u těchto obvodů vede k bezpečnému uzavření všech výstupních tranzistorů.
- **Časování:** Délka této fáze je určena konstantou `OFFTIME`.
#### 2.3.5.2. Fáze On-time (Zobrazení)

Pokud uplyne mrtvý čas, přepne se automat do fáze zobrazení.

- **Logika výběru dvojic:** Protože systém využívá dva dekodéry pro šest digitronů, jsou číslice spínány po dvojicích. Indexování `pairIndex` určuje, která dvojice (např. hodiny-desítky a minuty-jednotky) bude v daném cyklu aktivována.
- **Mapování dat (Look-Up Tables):** Pro převod hodnot z procesoru na konkrétní piny portů jsou využity vyhledávací tabulky `nix_LUT_upper` a `nix_LUT_downer`. Tyto tabulky korigují případné proházené zapojení cest na plošném spoji, což zjednodušuje návrh PCB.
- **Aktivace výstupu:** Nejprve jsou nastavena data na portech B a D a následně je sepnuta příslušná anoda na portu C. Tím je zajištěno, že v momentě sepnutí vysokého napětí jsou již katody správně navoleny.    

#### 2.3.5.3. Efektivní manipulace s registry a bitové operace
Pro ovládání výstupních pinů a konfiguraci periférií mikrokontroléru ATmega328P není v ISR kvůli rychlosti využívána knihovní funkce `digitalWrite()`, ale **přímý přístup k portům** . Tento přístup využívá bitové operátory, které umožňují měnit stavy jednotlivých pinů v rámci jednoho instrukčního cyklu procesoru, aniž by byly ovlivněny ostatní piny na stejném portu.

#### 2.3.5.4. Selektivní nulování bitů pomocí operátorů `&= ~`

V rutině přerušení je pro vypnutí všech anod využita operace bitového součinu s negovanou maskou: `PORTC &= ~0x07;`

Tento zápis funguje ve třech krocích:

1. **Maska (`0x07`):** Představuje binární hodnotu `00000111`. Tyto bity odpovídají pinům PC0, PC1 a PC2 (anody). *PC = Port C*
2. **Bitová negace (`~`):** Převrátí masku na `11111000`.
3. **Bitový součin (`&=`):** Provede logické AND mezi aktuálním stavem portu a negovanou maskou. Výsledkem je, že piny definované v masce jsou vynulovány (logická 0), zatímco piny PC3 až PC7 zůstávají beze změny (protože X AND 1=X).

#### 2.3.5.5. Zachování stavu a zápis dat (Bitmasking)

Složitější operace nastává při zápisu dat pro katody, kde je nutné zapsat 4 bity (nibble) pro dekodér MH74141, ale zároveň nesmíme změnit zbývající 4 bity portu, které mohou sloužit jinému účelu: `PORTD = (PORTD & 0x0F) | (nix_LUT_upper[val] << 4);`

Tento řetězec operací zajišťuje tzv. **izolovaný zápis**:

- **`(PORTD & 0x0F)`:** Maska pro horní 4 bity portu D (vynuluje je), zatímco dolní 4 bity (0–3) ponechá beze změny.
- **`(val << 4)`:** Bitový posun posune 4bitovou hodnotu číslice z dolního nibblu do horního.
- **Bitový součet (`|`):** Spojí původní dolní bity s novými horními bity a výsledek zapíše do registru portu.

#### 2.3.5.6. Výhody oproti standardním funkcím

Hlavním důvodem pro toto řešení je **rychlost a determinismus**. Zatímco funkce `digitalWrite()` v sobě nese režii spojenou s vyhledáváním pinu v tabulce, kontrolou módu pinu a vypínáním PWM, bitová operace se v jazyce symbolických instrukcí (Assembler) přeloží na jedinou instrukci `CBI` (Clear Bit) nebo `SBI` (Set Bit). To je klíčové pro stabilitu multiplexu, kde i nepatrné zpoždění při přepínání může způsobit nerovnoměrný jas nebo viditelné artefakty v obraze.
#### 2.3.5.7. Význam klíčového slova `volatile`

Všechny globální proměnné, které jsou modifikovány uvnitř ISR a zároveň čteny v hlavní smyčce (např. `timer_counter`, `isBlanking`, `pairIndex`), musí být deklarovány s modifikátorem **`volatile`**.

**Proč je to nutné?** Moderní kompilátory (v mém případě `avr-gcc`) provádějí agresivní optimalizace. Pokud kompilátor v hlavní smyčce vidí, že se hodnota proměnné v daném bloku kódu nikde nemění, může její hodnotu pro zrychlení běhu uložit do jednoho z pracovních registrů CPU namísto opakovaného čtení z paměti RAM. Protože se však přerušení (ISR) může aktivovat kdykoliv a změnit hodnotu v RAM, hlavní smyčka by pracovala se zastaralou hodnotou v registru, což by vedlo k logickým chybám nebo zacyklení programu.

> Klíčové slovo **`volatile`** dává kompilátoru jasný pokyn: _"Tato proměnná se může změnit vně aktuálního toku programu (přerušením), proto ji nikdy neukládej do mezipaměti a při každém přístupu ji znovu načti z adresy v RAM."_
#### 2.3.5.8. Optimalizace pomocí `uint_fast8_t`

V rutině přerušení, která se spouští s frekvencí 8kHz, hraje roli každá instrukce. Pro lokální proměnné a pomocné výpočty byl zvolen datový typ **`uint_fast8_t`**.

Tento typ, definovaný v knihovně `<stdint.h>`, instruuje kompilátor, aby pro danou proměnnou vybral **nejrychlejší dostupný celočíselný typ** o šířce alespoň 8 bitů pro danou architekturu.

- Na 8bitové architektuře AVR (ATmega328P) odpovídá standardnímu `uint8_t` (jednobajtový typ).
- Použití tohoto typu však dává kompilátoru najevo, že prioritou je rychlost zpracování, nikoliv minimální spotřeba paměti.

V kontextu ISR to slouží jako „programátorský reminder“: kód uvnitř přerušení musí být co nejefektivnější a nejkratší, aby nedocházelo k příliš dlouhému blokování hlavního programu nebo k rekurzivnímu vyvolání přerušení.
### 2.3.6. Datová struktura a hlavní smyčka
V hlavní smyčce programu (`loop`) probíhá pouze výčet aktuálního času z RTC a jeho rozklad na jednotlivé číslice (hodiny, minuty, sekundy). Tyto hodnoty jsou ukládány do globálního pole (bufferu), ze kterého si je rutina ISR při každém volání vybírá. Toto oddělení logiky výpočtu a logiky zobrazování zvyšuje přehlednost kódu a stabilitu systému.

## 2.4. Měření času a modul RTC DS3231
Aby hodiny plnily svou primární funkci s vysokou přesností, byl do systému integrován modul reálného času **DS3231**. Na rozdíl od vnitřních čítačů mikrokontroléru, které jsou závislé na stabilitě krystalu procesoru a teplotě okolí, disponuje DS3231 vlastní časovou základnou a záložní baterií, což zaručuje uchování času i po odpojení hlavního napájení.

![[Schema_DS3231.png]]
<center>obr. 5 - schéma zapojení modulu RTC DS3231</center>
### 2.4.1. Komunikační rozhraní a vlastní knihovnička
Komunikace mezi kontrolérem ATmega328P a RTC modulem probíhá přes sériovou sběrnici **I2C**  . Pro obsluhu modulu jsem se rozhodl nevyužívat hotové knihovny třetích stran, ale vytvořit **vlastní knihovničku `Rtc`**. Tento přístup umožnil:

- Minimalizaci výsledného kódu (vypuštění nepotřebných funkcí).
- Přímou kontrolu nad registry modulu.
- Hlubší pochopení protokolu komunikace.
- Zopakovat si základy OOP
### 2.4.2. Sběrnice I2C (Inter-Integrated Circuit)
Pro komunikaci s modulem RTC je využita sériová sběrnice **I2C** . Tato sběrnice pracuje na principu **Master-Slave** a k přenosu dat využívá pouze dva vodiče: **SDA** (Serial Data) pro přenos dat a **SCL** (Serial Clock) pro synchronizaci hodinových pulzů. Unikátnost I2C spočívá v tom, že obě linky jsou zapojeny v režimu s otevřeným kolektorem, což vyžaduje použití **pull-up rezistorů** k udržení klidové logické úrovně. Komunikace probíhá adresně – mikrokontrolér (Master) vysílá na sběrnici unikátní 7bitovou adresu zařízení (v případě DS3231 je to `0x68`) (7 bitů proto, že 8mý se využívá jako podmínka START), čímž probudí konkrétní čip k příjmu nebo odesílání dat. Tento mechanismus umožňuje připojit na stejnou dvojici vodičů více různých periférií (např. další senzory nebo displeje), což výrazně šetří I/O piny mikrokontroléru.

Tato sběrnice není primárně určena ke komunikaci P2P (Peer to Peer). V mém případě bylo této sběrnice využito, protože to je jediný způsob komunikace s čipem DS3231.
### 2.4.3. Práce s daty v BCD formátu
DS3231 ukládá časové údaje v registrech ve formátu **BCD** (Binary Coded Decimal). V tomto formátu reprezentuje každá čtveřice bitů (nibble) jednu dekadickou číslici. Pro korektní zobrazení na digitronech a výpočty v procesoru obsahuje knihovna převodní funkce:

- **`decToBcd`**: Převádí standardní desítkové číslo na formát pro zápis do RTC.
- **`bcdToDec`**: Převádí data načtená z RTC na desítkovou soustavu pro další zpracování.

### 2.4.4. Implementace Budíků a vteřinové reference
Unikátní vlastností mé implementace je využití vnitřního alarmu **A1** k synchronizaci systému.

- Funkce `initAlm1()` nastavuje alarm tak, aby generoval vlaječku (flag) **každou sekundu**.
- V hlavní smyčce programu se následně testuje `getAlm1FlagTrigger()`. Pokud je vlaječka aktivní, proběhne vyčtení nového času a aktualizace displeje.

Tento přístup je mnohem efektivnější než neustálé dotazování na čas v každém průchodu smyčkou (polling), čímž se nezahlcuje pásmo sběrnice I2C.

Alarm A2 je potom uživatelsky nastavitelný a spouští svoji vlaječku, pokud sedí minuty a hodiny. Funkce budíku.
### 2.4.5. Monitorování teploty a Stop Flag
Modul DS3231 obsahuje integrované teplotní čidlo, které slouží k jemné korekci frekvence oscilátoru. Moje knihovna umožňuje tyto hodnoty vyčítat pomocí funkcí `readTemp()` a `getTemp()`. Zobrazení teploty na digitronech je pak zajímavým doplňkem funkčnosti hodin.

Důležitým bezpečnostním prvkem je správa **OSF (Oscillator Stop Flag)** pomocí funkcí `getStopFlag()` a `resetStopFlag()`. Tento bit v status registru signalizuje, že došlo k výpadku napájení (včetně záložní baterie) a čas v modulu již není validní.

## 2.5. Uživatelské rozhraní: Kapacitní detekce dotyku

Pro ovládání hodin a nastavování parametrů (čas, budík) jsem se rozhodl nevyužít klasická mechanická tlačítka, která by narušovala čistý design přístroje. Namísto toho byla implementována **kapacitní dotyková detekce**, která umožňuje ovládat hodiny pouhým dotykem poblíž (teoretiky i na) kovové plošky, jež bude instalována pod krytem.

### 2.5.1. Princip měření kapacity pomocí interní ADC

Metoda detekce je založena na měření změn kapacity lidského těla. Využívá se k tomu vnitřní **Sample-and-Hold (S&H)** kondenzátor ADC převodníku. Proces měření v mé knihovně `Touch` probíhá v několika krocích:

1. **Nabíjení/Vybíjení:** Pin je nejprve nastaven jako vstup s interním pull-up rezistorem, čímž se „nabije“ parazitní kapacita připojeného dotykového senzoru.
2. **Vybíjení vnitřního kondenzátoru:** Pomocí registru `ADMUX` (nastavením kanálu `0b11111`) je vnitřní kondenzátor ADC převodníku krátce připojen k zemi, aby byl zcela vybit.
3. **Sdílení náboje:** Pin senzoru je následně přepnut na standardní analogový vstup. V tomto momentě dojde k přerozdělení náboje mezi externí dotykovou plochou a vnitřním kondenzátorem ADC.
4. **Měření:** ADC převodník změří výsledné napětí. Pokud se senzoru dotkne člověk, zvýší se jeho kapacita, změní se poměr rozdělení náboje a naměřená digitální hodnota se změní.

### 2.5.2. Softwarové zpracování, čištění dat a adaptivní baseline

Protože kapacitní měření je náchylné na šum a okolní vlivy (vlhkost, teplota, parazitní pole), implementoval jsem v knihovně několik mechanismů pro zvýšení spolehlivosti:

- **Oversampling:** Funkce `Read()` provádí měření v cyklu (`samples`) a následně počítá průměrnou hodnotu, což efektivně filtruje náhodné špičky napětí.
- **Adaptivní Baseline:** Program si neustále udržuje referenční hodnotu (`baseline`), která představuje klidový stav bez dotyku. Tato hodnota je průběžně aktualizována pomocí exponenciálního klouzavého průměru (koeficient `alpha`). To umožňuje senzoru automaticky se nakalibrovat na změny okolního prostředí. 
- **Hystereze:** Aby nedocházelo k vícenásobným stiskům (zakmitávání) při přiblížení prstu, je v kódu implementována hystereze. Pro aktivaci dotyku je nutné překročit `threshold`, ale pro jeho uvolnění musí hodnota klesnout hlouběji pod tuto hranici (`threshold / 2`).

### 2.5.3. Konfigurace z paměti EEPROM

Parametry senzoru, jako je citlivost (`threshold`) nebo rychlost adaptace (`alpha`), nejsou v kódu pevně definovány, ale jsou načítány z paměti pomocí třídy `PresetMemory`. To umožňuje jemné doladění citlivosti dotyku bez nutnosti znovu programovat celý mikrokontrolér, což je klíčové pro finální kalibraci hodin v pouzdře.

## 2.6. Zvuková signalizace a generování tónů
Nedílnou součástí hodin s funkcí budíku je akustický výstup. Pro tento účel byl do zapojení přidán piezoelektrický měnič, který je řízen přímo jedním z digitálních pinů mikrokontroléru ATmega328P.

### 2.6.1. Princip generování zvuku pomocí PWM a Timer0
Generování konkrétních tónů (frekvencí) je založeno na principu **PWM (Pulse Width Modulation)**, respektive na vytváření obdélníkového signálu o proměnné frekvenci. Mikrokontrolér využívá své vnitřní časovače k rychlému přepínání stavu pinu mezi logickou nulou a jedničkou.

- **Frekvence:** Určuje výšku tónu.
- **Střída (Duty Cycle):** Pro generování zvuku je fixně nastavena na 50%, což zajišťuje maximální efektivitu přenosu energie do měniče a čistý zvuk. 

V softwaru je pro tento účel využita funkce `tone()`, která konfiguruje příslušný Timer0 tak, aby na pozadí generoval požadovaný kmitočet bez nutnosti zásahu hlavní programové smyčky.

### 2.6.2. Architektura knihovničky `almSound`

Pro přehrávání melodií jsem navrhl třídu `almSound`, která řeší interpretaci hudebních dat. Melodie jsou uloženy v úsporném textovém formátu, kde dvojice znaků definuje délku trvání a výšku noty (např. `'4C'` pro notu C po 4 intervaly).

**Klíčové vlastnosti implementace:**
- **Neblokující řízení:** Funkce `loop()` využívá systémový čas `millis()` k odpočítávání délky jednotlivých not. Na rozdíl od standardní funkce `delay()` tak přehrávání hudby nezastaví zbytek programu – hodiny stále měří čas a obsluhují multiplex displeje i během buzení.
- **Interpretace not:** Pomocí funkce `noteToFreq` a rozsáhlého seznamu maker (`#define NOTE_...`) jsou znaky (jako 'C', 'D', 'E') převáděny na konkrétní hodnoty v Hertzech. Knihovna podporuje dvě oktávy a speciální znak 'X' pro pomlku.
- **Režimy přehrávání:** Systém rozlišuje mezi jednorázovým přehráním (`oneShot`) a nekonečnou smyčkou, což je ideální pro stupňující se vyzvánění budíku.
- **Rychlost intervalu:** nastavuje jakou dobu trvá jeden interval

### 2.6.3. Softwarový automat (State Machine)
Přehrávač funguje jako jednoduchý stavový automat. V každém kroku určeném tempem (BPM):
1. Zkontroluje, zda již uplynul čas aktuální noty (`accumulatedWaitTime`).
2. Vyhledá v poli melodie další notu.
3. Nastaví novou frekvenci pomocí `tone()` nebo zvuk ukončí pomocí `noTone()`.
4. Pokud narazí na ukončovací znak, buď melodii ukončí, nebo se vrátí na začátek.

Tento systém umožňuje snadnou úpravu melodií pouhou změnou textového řetězce, bez nutnosti zasahovat do logiky přehrávače. 

## 2.7. Terminál přes sériovou linku
Díky jednoduchému uživatelskému rozhraní je nastavování času zcela nemožné. Všechna nastavení jsou tedy realizovány pomocí externího zařízení, na němž je spuštěn sériový terminál.
To zajišťuje intuitivní a nedebilní nastavování.

S hodinami je možné komunikovat přes sériovou linku o rychlosti 115 200 baud/s s nastavením 8N1 pomocí jednoduché konzole. Příkazy jsou zadávány ve formátu a vždy velkými písmeny:
`<prefix><příkaz><parametr>`
kdy jednotlivé části mohou být odděleny libovolnými počty mezer

*pozn. Na hardware sériovou linku je možné připojit modul bluetooth sériového převodníku. S hodinami je potom možné komunikovat bezdrátově.*

prefix je definován v kódu jako `AT`
 zde je tabulka příkazů:

| příkaz | slovy                      | funkce                                                                                     | parametr                                          | základní hodnota |
| ------ | -------------------------- | ------------------------------------------------------------------------------------------ | ------------------------------------------------- | ---------------- |
| EXT    | exit                       | ukončí komunikaci                                                                          | -                                                 | -                |
| SCK    | set clock                  | nastavení hodin                                                                            | čas ve formátu HH:MM:SS                           | -                |
| SDT    | set date                   | nastavení datumu                                                                           | datum ve formátu DD.MM.RR nebo DD.MM.RRRR \[[^1]] | -                |
| SAL    | set alarm                  | nastavení budíku                                                                           | čas budíku ve formátu HH:MM                       | -                |
| SAV    | save to prom               | uložení hodnot do programovatelné paměti                                                   | -                                                 | -                |
| CDT    | config display temp        | zapnutí nebo vypnutí zobrazování teploty (orientační)                                      | 1 pro zapnutí,0 pro vypnutí                       | 0                |
| CTS    | configure test segments    | zapnutí nebo vypnutí testu segmentů po zapnutí                                             | 1 pro zapnutí,0 pro vypnutí                       | 1                |
| CRR    | configure radar returntime | nastavení času automatického vypnutí, pokud radar nedetekuje                               | číslo v sekundách, < 250                          | 30               |
| CMR    | configure menu returntime  | nastavení času automatického návratu na zobrazení hodin, po nečinnosti na hlavním tlačítku | číslo v sekundách, < 250                          | 10               |
| TSA    | touch samples              | nastavení množství vzorků pro detekci dotyku                                               | číslo, < 1000                                     | 100              |
| TTR    | touch treshold             | nastavení prahu pro detekci dotyku                                                         | číslo, < 250                                      | 40               |
| TAL    | touch alpha                | nastavení parametru $\alpha$ pro detekci dotyku                                            | číslo, < 25                                       | 8                |
| MAL    | melody alarm               | nastavení melodie pro budík (melodie se opakuje)                                           | <trvání>;\<melodie> \[[^2]]                       | nokia ringtone   |
| MOK    | melody ok                  | nastavení potvrzovací melodie (one-shot)                                                   | <trvání>;\<melodie> \[[^2]]                       | tididing         |
| MER    | melody error               | nastavení chybové melodie (one-shot)                                                       | <trvání>;\<melodie> \[[^2]]                       | nuh uh           |
| DSS    | display slot seconds       | nastavení,zda se mají protáčet i jednotky sekund                                           | 1 pro zapnutí,0 pro vypnutí                       | 0                |
| DAU    | display animation update   | nastavení času mezi jednotlivými kroky animace (přílet a odlet)                            | hodnota v milisekundách, < 250                    | 150              |
| DSU    | display seconds update     | nastavení času mezi otočkami u sekund                                                      | hodnota v milisekundách, < 250                    | 75               |
| DMU    | display mins/hours update  | nastavení času mezi otočkami minut/hodin                                                   | hodnota v milisekundách, < 250                    | 75               |
| DOT    | display dot ontime         | nastavení času, po který jsou aktivní tečky \[[^3]]                                        | hodnota v milisekundách, < 800                    | 250              |
| FRS    | factory reset              | tovární nastavení                                                                          | -                                                 | -                |
**důležité: mimo nastavení času (SCK, SDT, SAL) je třeba hodnoty ukládat příkazem SAV. Pokud se tak nestane, hodnoty se po restartu (ztráta napájení, vypnutí, nebo stisk tlačítka reset) vrátí zpět na původní hodnoty!**
*\[1]: RRRR je formát začínající dvojčíslím 20XX, pokud vložíte hodnotu 19XX, tak jste si úspěšně zablokovali program hodin. Hodně štěstí.*
*\[2]: trvání je doba mezi jednotlivými notami. formát melodie je následující: <číslo><písmeno>, kdy číslo je trvání noty (násobky trvání), a písmeno je nota (tabulka not je popsána v části program). melodie MUSÍ být ukončena ukončovacím znakem '0'*
*\[3]: funkce není v prototypu zapojena*

správný příkaz tedy může vypadat takto: 
`> AT SCK 12:34:56`

Hodiny odpovídají pomocí dvouznakových odpovědí. Odpověď může být buď
`> OK` - příkaz proveden, nebo `> E<číslo_chyby>`, indikující chybu.

tabulka odpovědí:

| odpověď | vysvětlení     | co se stalo?                               |
| ------- | -------------- | ------------------------------------------ |
| E0      | neznámý příkaz | zadali jste špatný příkaz. Překlep.        |
| E1      | nevalidní data | parametr je zadán mimo jeho definiční obor |
| E2      | interní chyba  | nikdy by se nemělo stát                    |
| E3      | overflow       | zadaný příkaz je příliš dlouhý (moc mezer) |
| OK      | provedeno      | příkaz se správně provedl                  |
# 3. výroba
## 3.1. tištěný spoj
Teoretický návrh byl následován fází fyzické realizace, která zahrnovala výrobu desky plošných spojů (PCB), osazování součástek a kritickou fázi oživování vysokonapěťových částí.
### 3.1.1. Návrh a výroba PCB

Návrh plošného spoje byl realizován v prostředí KiCad EDA. Vzhledem k přítomnosti napětí okolo 170V bylo nutné dodržet bezpečné izolační vzdálenosti mezi cestami vysokého napětí a nízkonapěťovou logikou, aby se předešlo vzniku svodů a jiskření.

- **Topologie:** Deska je navržena jako jednovrstvá s dvěma rozdílnými plochami rozlité mědi (GND planes) na spodní straně pro minimalizaci elektromagnetického rušení.
- **Výroba:** Pro prototyp byla zvolena cesta amatérské výroby pomocí tonerového přenosu a leptání chloridem železitým, což se ukázalo jako špatný nápad. deska zoxidovala už druhý den (nemám nepájivou masku),  některé cesty se přerušily a impedanční homogenita je zaručená maximálně na centimetru čtverečním. Mimo to se mi také podařilo nasekat na desku několik hardwarových chyb, jež bylo potřeba opravit. Deska tedy vypadá jako průměrný ležák na jednotce intenzivní péče, ale funguje. Zatím.

### 3.1.2. Osazování a pájení
Osazování probíhalo od nejnižších součástek (rezistory, diody) po nejvyšší (kondenzátory). Dceřiná deska s mikrokontrolérem byla osazena jako poslední. Zvláštní pozornost byla věnována:

- **Výkonovým prvkům:** MOSFET a indukčnost boost měniče byly umístěny tak, aby kolem nich mohl proudit vzduch pro lepší odvod tepla.
- **Čistotě:** Po pájení byla deska důkladně očištěna od zbytků tavidla (isopropylalkoholem). U vysokonapěťových obvodů může být znečištěné tavidlo mírně vodivé, což způsobuje nestabilitu zdroje nebo parazitní svit číslic.

### 3.1.3. Oživování a testování
Oživování probíhalo v několika krocích, aby se minimalizovalo riziko zničení drahých komponent (digitronů a mikrokontroléru):
1. **Test zdroje (Low Voltage):** Nejprve byla osazena pouze nízkonapěťová část a ověřena přítomnost 12V pro logiku (zdroj 5V je instalován na dceřiné desce mikrokontroléru).
2. **Oživení Boost měniče:** Bez osazených digitronů a mikrokontroléru byl spuštěn měnič napětí. Pomocí trimru bylo nastaveno výstupní napětí na 170V a sledována stabilita a teplota spínacího tranzistoru při umělé zátěži.
3. **Softwarové oživení:** Po ověření napájecích větví byl vložen mikrokontrolér s testovacím programem pro ověření komunikace s RTC a funkčnosti multiplexu.
4. **Finální test:** Jako poslední byly osazeny digitrony. V této fázi byl doladěn proud protékající katodami pomocí anodových rezistorů, aby byl jas vyvážený a nedocházelo k překračování jmenovitých parametrů výbojek.
## 3.2. 3D tištěný kryt
Vzhledem k unikátním rozměrům použitých digitronů a potřebě bezpečně izolovat vysokonapěťovou část byl kryt hodin navržen na míru a realizován pomocí technologie **3D tisku (FDM)**.

- **Materiál a design:** Pro tisk byl zvolen materiál **PETG** (tištěno z průhledného filamentu protože jsem ho prostě měl a tečka). Tento materiál nabízí dobrou tepelnou odolnost a mechanickou stabilitu. Design krytu byl navržen v CAD softwaru s důrazem na minimalismus, aby vynikly samotné digitrony jako dominantní prvek. Kryt je rozdělen na základnu, ve které je skryto PCB, a horní masku, která přesně kopíruje patice výbojek.
- **Integrace dotykového ovládání:** Klíčovým prvkem konstrukce je tenká stěna v místě dotykového senzoru. Kapacitní senzor popsaný v předchozích kapitolách je umístěn těsně pod povrchem plastu, což umožňuje ovládání hodin pouhým přiložením prstu na vnější stranu krytu. Toto řešení eliminuje potřebu děr a chrání vnitřní elektroniku před prachem a nečistotami.
- **Bezpečnost a chlazení:** V krytu jsou integrovány větrací otvory, které zajišťují pasivní cirkulaci vzduchu. To je nezbytné pro chlazení výkonové tlumivky a MOSFETu boost měniče, které při dlouhodobém provozu generují zbytkové teplo. Vnitřní sloupky pro uchycení PCB zajišťují pevnou fixaci desky a zároveň definují bezpečnou vzdálenost vysokonapěťových cest od spodní strany krytu.

![[Case_iso.png|534]]<center>obr. 6 - isometrické zobrazení krytu</center>
![[Case_explowiew.png|610]]<center>obr. 7- explodované zobrazení vnitřní struktury a uspořádání.</center>

K návrhu byl použit software OnShape.com. Kryt je řešen jako 6ti dílný - spodní díl (zelený) v sobě ukrývá drážky pro přední krytku (modrá), drážku pro paticemi spojené poloviny jejich držáku (oranžová, červená) a zadní panel (šedá). Mimo tojsou zde instalovány také nožičky s úhlem 5°, vyvýšené výstupky pro usazení PCB a ventilační díra pro DS3231 - aby bylo měření teploty nějak vypovídající a něměřilo teplotu uvnitř krabice. Přední a zadní díly potom ukrývají šestici děr pro šroubky M3, které drží celou krabici dobromady. V zadním díle je potom instalováno tlačítko restartu, DB9 sériový konektor, dírka pro napájecí kabely, výřez pro reproduktorek a pár slotů pro chlazení. Celá krabice je dokončena svrchním dílem (světle modrá), v němž jsou zeslabeny stěny pro pásku dotykového senzoru a místo pro radar. Krabička drží pospolu pomocí dvou šestic šroubů M3, šroubovaných skrz přední a zadní díl zepředu a zezadu do matiček, umístěných do držáků k tomu určených ve spodním a svrchním díle.
![[Case_front.png]]<center>obr. 8 - pohled zepředu</center>
![[Case_back.png]]<center>obr. 9 - pohled zezadu</center>
# 4. Závěr

Cílem této práce bylo navrhnout a realizovat plně funkční digitronové hodiny, které spojují estetiku historické techniky s moderními principy embedded systémů. Během realizace se podařilo úspěšně vyřešit problematiku zvyšujícího měniče vysokého napětí, implementovat stabilní multiplexní řízení a vytvořit robustní softwarovou základnu v jazyce C++.

Projekt mě naučil jak práce s nízkoúrovňovým programováním registrů, tak OOP, optimalizovat kód pro reálný čas a řešit fyzikální úskalí spojená s rušením a kapacitní detekcí. Výsledkem je zařízení, které je nejen esteticky unikátní, ale díky použitým technologiím (DS3231, EEPROM backup, ochrana katod) také vysoce spolehlivé a připravené pro dlouhodobý provoz. Do budoucna se nabízí rozšíření o modul pro synchronizaci času přes Wi-Fi pomocí protokolu NTP, čímž by se hodiny staly zcela bezúdržbovými.