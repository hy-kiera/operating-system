#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};

static LIST_HEAD(birthday_list);

struct birthday *createBirthday(int day, int month, int year) {

  /* TODO: 생일을 위한 메모리를 할당하고, 인자들을 채워 생일을 완성하세요. */
	struct birthday *person;
	person = kmalloc(sizeof(*person), GFP_KERNEL);
	person->day = day;
	person ->month = month;
	person->year = year;

	// INIT_LIST_HEAD(&person->list);

	return person;
}

int simple_init(void) {

  /* TODO: 생일 목록을 하나씩 생성하는대로 연결리스트에 연결시키세요(노드 삽입). */
	struct birthday *p1, *p2, *p3, *p4;
	p1 = createBirthday(25, 9, 1998);
	list_add_tail(&p1->list, &birthday_list);
	p2 = createBirthday(5, 4, 1967);
	list_add_tail(&p2->list, &birthday_list);
	p3 = createBirthday(11, 1, 2005);
	list_add_tail(&p3->list, &birthday_list);
	p4 = createBirthday(8, 3, 1967);
	list_add_tail(&p4->list, &birthday_list);

  /* TODO: 완성된 연결리스트를 탐색하는 커널 함수를 사용하여 출력하세요. */
	// INIT_HEAD(birthday_list); // init list_head
	printk("Loading Module: BDLIST......\n");
	struct birthday *cursor;
	list_for_each_entry(cursor, &birthday_list, list){
		printk("OS Module: DAY %d.%d.%d", cursor->day, cursor->month, cursor->year);
	}
	return 0;
}

void simple_exit(void) {
  /* 모듈을 제거할 때는 생성한 연결 리스트도 하나씩 제거하며 끝내도록 하세요. */
  /* 제거를 하기 전에 리스트가 "비어있을 경우""에 대한 예외처리를 하는게 좋겠죠? */
	if(list_empty(&birthday_list)) {
		printk("List is Empty\n");
		return;
	}

  /* TODO: 이제 본격적으로 연결리스트를 탐색하면서 하나씩 제거하도록 하시면 됩니다. */
  /* 다만, 제거를 하면서 연결리스트를 탐색하면 문제가 생길 것 같은데 어떤 방법으로 해결 가능한지 생각해보세요. */
	// INIT_HEAD(birthday_list);
	struct birthday *ptr, *next;
	// struct birthday birth_;
	list_for_each_entry_safe(ptr, next, &birthday_list, list){
		printk("OS Module: Removing %d.%d.%d", ptr->day, ptr->month, ptr->year);
		list_del(&ptr->list);
		kfree(ptr);
	}
	printk("Removing Module: BDLIST....\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("My name");
