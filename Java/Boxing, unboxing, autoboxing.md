## Boxing
Wraps a primitive value in an object (wrapped class). 

```Java
int i = 10;
Integer i = new Integer(10);    // boxing
```
## Unboxing
Extracts the primitive value from a object to a primitive type.

```Java
Integer i = new Integer(10);
int v = i.intValue();          // unboxing
```

## Autoboxing

The **Autoboxing** consists in an automatic conversion to a primitive type to an object, and other way round (viceversa).
```Java
int i = 10;
i = new Integer(10);          // autoboxing
i = i.intValue();             // autoboxing (unboxing)
```

## Wrapper Class
![[Screenshot 2025-03-03 alle 16.34.13.png]]