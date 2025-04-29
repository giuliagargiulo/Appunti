## Upcast
Upcasting a class is **always safe**, because all the subclasses are also members of the superclass. For example:
```Java
Item item = new CD();    // Correct!
Item item = new DVD();   // Correct!
```

In the inheritance tree, the promotion is performed upwards (we considered a subclass like a superclass). Like in the previous example, CD and DVD are considered like Items.

![[Screenshot 2025-03-03 alle 16.34.25.png|400]]

---
## Downcast
Downcast is not safe, because can be rejected by the compiler or at runtime.
In the following example, code is rejected by the compiler, because an item could be a DVD, but also a CD or a VideoGame.

```Java
void m (Item item){
	DVD dvd = item;   // Compilation ERROR!
}
```

>[!Warning]
>Implicit down-casting is not allowed (non è permesso).

Is possible to down-cast with an explicit cast, like in the following example, but also in this case item could be a DVD but also a CD or VideoGame, so this code can generate a **runtime error**.

```Java
void m (Item item){
	DVD dvd = (DVD) item;   // Runtime ERROR!
}
```

So, the safest way to do a down-cast is using  the keyword `instanceof`:
```Java
void m (Item item){
	if(item instanceof DVD)
		DVD dvd = (DVD) item;   // Correct!
}
```
---
