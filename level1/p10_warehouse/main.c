#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAX_NAME_LEN 50
#define MAX_ITEMS 100

// 商品结构体
typedef struct {
    char model[MAX_NAME_LEN];  // 型号
    int quantity;              // 数量
} Product;

// 库存管理系统
typedef struct {
    Product items[MAX_ITEMS];  // 商品数组
    int count;                 // 当前商品数量
} Inventory;


// 文件操作
void load_inventory(Inventory *inv, const char *filename);
void save_inventory(Inventory *inv, const char *filename);

// 核心功能
void show_inventory(Inventory *inv);
void stock_in(Inventory *inv);      // 入库
void stock_out(Inventory *inv);     // 出库

// 辅助函数
int find_product(Inventory *inv, const char *model);
void add_product(Inventory *inv, const char *model, int quantity);
void menu_display();


void add_product(Inventory *inv, const char *model, int quantity)
{
    Product product;
    product.quantity = quantity;
    strcpy(product.model, model);
    inv->items[inv->count++] = product;
}


int find_product(Inventory *inv, const char *model)
{
    for (int index = 0; index < inv->count; index++)
    {
        if (strcmp(inv->items[index].model, model) == 0)
        {
            return index;
        }
    }
    return -1;
}



void load_inventory(Inventory *inv, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file) {
        fread(inv, sizeof(Inventory), 1, file);
        fclose(file);
    }
}


void save_inventory(Inventory *inv, const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (file)
    {
        fwrite(inv, sizeof(Inventory), 1, file);
        fclose(file);
    }
}


void show_inventory(Inventory *inv)
{
    for (int i = 0; i < inv->count; i++)
    {
        printf("%s, quantity: %d\n", inv->items[i].model, inv->items[i].quantity);
    }
}


void menu_display ()
{
    printf("\n=== 简单进销存系统 ===\n");
    printf("1. 显示存货列表\n");
    printf("2. 入库\n");
    printf("3. 出库\n");
    printf("4. 退出程序\n");
    printf("=====================\n");
}


void stock_in(Inventory *inv)
{
    char model[MAX_NAME_LEN];
    int quantity;

    printf("请输入商品型号: ");
    scanf("%s", model);
    printf("请输入入库数量: ");
    scanf("%d", &quantity);

    int index = find_product(inv, model);
    if (index != -1) {
        // 商品已存在，增加库存
        inv->items[index].quantity += quantity;
    } else {
        // 新商品，添加到库存
        add_product(inv, model, quantity);
    }
    printf("入库成功！\n");
}

void stock_out(Inventory *inv) {
    char model[MAX_NAME_LEN];
    int quantity;

    printf("请输入商品型号: ");
    scanf("%s", model);
    printf("请输入出库数量: ");
    scanf("%d", &quantity);

    int index = find_product(inv, model);
    if (index == -1) {
        printf("商品不存在！\n");
        return;
    }

    if (inv->items[index].quantity < quantity) {
        printf("库存不足！当前库存: %d\n", inv->items[index].quantity);
        return;
    }

    inv->items[index].quantity -= quantity;
    printf("出库成功！\n");
}


int main() {
    SetConsoleOutputCP(65001);

    Inventory inventory = {0};
    int choice;

    // 程序启动时加载数据
    load_inventory(&inventory, "inventory.dat");

    do {
        menu_display();
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch(choice) {
        case 1: show_inventory(&inventory); break;
        case 2: stock_in(&inventory); break;
        case 3: stock_out(&inventory); break;
        case 4:
            save_inventory(&inventory, "inventory.dat");
            printf("程序退出，数据已保存！\n");
            break;
        default:
            printf("无效选择，请重新输入！\n");
        }
    } while(choice != 4);

    return 0;
}