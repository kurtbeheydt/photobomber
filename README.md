# materiaallijst
## Bord zelf
- ir-leds: 3mm 24x8 = 192stuks
- SN74HC595N shift register: 3 stuks
- hef4017bp timer chip: 1 stuk
- soldeerbord
- bc547c npn transistor (of gelijkaardig): 24 stuks
- vnp20n07 mosfet transistor (of gelijkaardig): 8 stuks
- 1k Ohm weerstand: 24 stuks

## Voor de pijltjes:
- klein soldeerplaatje
- BD137 npn transistor (of gelijkaardig die 1A kan schakelen, afhankelijk van je ir-leds): 3 stuks
- ir-leds: 26 stuks

## Algemeen
- draad
- male en female header pins (voor het gemak van aansluiten van de kabels)
- veel tijd

## Opmerkingen:
- In pricipe moet je de ledjes een weerstand geven (33 Ohm op basis van 5v input stroom, 100 mA en voltage drop van 1.7V), maar aangezien ze enkel in burst mode gebruikt worden (ze gaan maar heel even aan en terug uit daarna), heb ik die weggelaten.
- De transistors moeten een groot genoeg Ampèrage kunnen schaken. Afhankelijk van je stroomverbruik van je leds, kan dat oplopen. Wil je bv 100mA voor elk ledje reserveren, komt dat op het volgende:
	- bc547c: 100mA
	- vnp20n07: 2.4A
	- BD137: 1A


