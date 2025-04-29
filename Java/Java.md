Per inizializzare un long e un float si utilizza: 
```java
long x = 16281020L;
float y = 34.54728f;
```
### Metodi stringhe

#### Equal
```java
String name = "Giulia";
boolean result = name.equals("Giulia");
System.out.println(result); // stampa true

boolean result = name.equals("giulia");
System.out.println(result); // stampa false

boolean result = name.equalsIgnoreCase("giulia");
System.out.println(result); // stampa true
```

#### Altri metodi
```java
String name = "Giulia";
int result = name.lenght(); // result = 6
char result = name.charAt(0);  // result = G
int result = name.indexOf("G"); // result = 0
boolean result = name.isEmpty(); // result = false
String result = name.trim(); // rimuove gli spazi vuoti prima e dopo la stringa
String result = name.replace('a','o'); // result = Giulio
```

