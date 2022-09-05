#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> //to stop for some seconds in the execution

typedef struct {
    int code;
    char name[30];
    float price;
} Product;

typedef struct {
    Product product;
    int quantity;
} Cart;

void infoProduct(Product product);
void menu();
void insertNewProduct();
void listOfProducts();
void showCart();
Product searchProductByCode(int code);
int * productsInTheCart(int code);
void finishPurchase();
void buy();

static int total_registered_products = 0;
static int total_products_cart = 0;
static Cart cart[50];
static Product products[50];


int main(){

    menu();
    return 0;
}

void infoProduct(Product product){
    printf("Code: %d \nName: %s \nPrice: %.2f\n", product.code, strtok(product.name, "\n"), product.price);
}

void menu(){
    printf("\tWelcome!\n");
    printf("Choice one option below:\n");
    printf("1 - Register a new product\n");
    printf("2 - List of products\n");
    printf("3 - Buy\n");
    printf("4 - View purchase\n");
    printf("5 - Finish purchase\n");
    printf("6 - Exit\n");

    int option;
    scanf("%d", &option);
    getchar(); //to fixe a bug in the line

    switch(option){
        case 1:
            insertNewProduct();
            break;
        case 2:
            listOfProducts();
            break;
        case 3:
            buy();
            break;
        case 4:
            showCart();
            break;
        case 5:
            finishPurchase();
            break;
        case 6:
            Sleep(2);
            exit(0);
        default:
            printf("Invalid option.\n");
            Sleep(2);
            menu();
            break;
    }

}
void insertNewProduct(){
    printf("Register a new product\n");
    printf("Insert the name: \n");
    fgets(products[total_registered_products].name, 30, stdin);
    printf("Insert the price: \n");
    scanf("%f", &products[total_registered_products].price);

    printf("The product %s has been registered successfully\n\n", strtok(products[total_registered_products].name, "\n"));

    products[total_registered_products].code = (total_registered_products + 1);
    total_registered_products++;

    menu();
}
void listOfProducts(){
    if(total_registered_products > 0){
        printf("\tList of Products\n");
        for(int i = 0; i < total_registered_products; i++){
            infoProduct(products[i]);
            printf("#################\n");
            Sleep(1);
        }
    } else {
        printf("The list is empty.\n\n\n");
        Sleep(3);
    }
    menu();
}
void showCart(){
    if(total_products_cart > 0){
        printf("\tProducts in the cart\n");
        for(int i = 0; i < total_products_cart; i++){
            infoProduct(cart[i].product);
            printf("Quantity: %d\n", cart[i].quantity);
            printf("######################\n");
            Sleep(1);
        }
    } else {
        printf("The cart is empty\n\n");
    }
    menu();
}
Product searchProductByCode(int code){
    Product prod;
    for(int i = 0; i < total_registered_products; i++){
        if(products[i].code == code){
            prod = products[i];
        }
    }
    return prod;

}
int * productsInTheCart(int code){
    int static regress[] = {0, 0};
    for(int i = 0; i < total_products_cart; i++){
        if(cart[i].product.code == code){
            regress[0] = 1; // there is the product in the cart
            regress[1] = i; //index of product in the cart
        }
    }
    return regress;
}

void buy(){
    if(total_registered_products > 0){
        printf("What is the code of product that you wish?\n");
        printf("\t\tProduct available\n");
        for(int i = 0; i < total_registered_products; i++){
            infoProduct(products[i]);
            printf("\n");
            Sleep(1);
        }
        int code;
        scanf("%d", &code);
        getchar();

        int validatedCode = 0;
        for(int i = 0; i < total_registered_products; i++){
            if(products[i].code == code){
                validatedCode = 1;

                if(total_products_cart > 0){
                    int * recurrence = productsInTheCart(code);

                    if(recurrence[0] == 1) {
                        cart[recurrence[1]].quantity++;
                        printf("Increased the quantity of product %s that already was in the cart\n",
                                strtok(cart[recurrence[1]].product.name, "\n"));
                                Sleep(3);
                                menu();
                    } else {
                        Product p = searchProductByCode(code);
                        cart[total_products_cart].product = p;
                        cart[total_products_cart].quantity = 1;
                        total_products_cart++;
                        printf("The product %s was add at the cart\n", strtok(p.name, "\n"));
                        Sleep(2);
                        menu();
                    }
                } else {
                    Product p = searchProductByCode(code);
                    cart[total_products_cart].product = p;
                    cart[total_products_cart].quantity = 1;
                    total_products_cart++;
                    printf("The product %s was add at the cart\n", strtok(p.name, "\n"));
                    Sleep(2);
                    menu();
                }
            }
        }
        if(validatedCode < 1){
            printf("Not found the product with the code %d\n", code);
            Sleep(3);
            menu();
        }
    } else {
        printf("Sorry! There are not products for selling\n\n");
        Sleep(3);
        menu();
    }
}

void finishPurchase(){
    if(total_products_cart > 0){
        float totalValue = 0.0;
        printf("\tProducts in the cart\n\n");
        for(int i = 0; i < total_products_cart; i++){
            Product p = cart[i].product;
            int quantity = cart[i].quantity;
            totalValue += p.price * quantity;
            infoProduct(p);
            printf("Quantity: %d\n", quantity);
            Sleep(1);
        }
        printf("Your bill is $ %.2f\n", totalValue);

        //clear this cart
        total_products_cart = 0;
        Sleep(5);
        menu();
    } else {
        printf("The cart is empty\n\n");
        Sleep(3);
        menu();
    }
}
