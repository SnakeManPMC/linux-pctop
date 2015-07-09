#define MAXUSERS 1000

/* defines the int-list */
struct int_list {
	int num;
	unsigned long long bytes;
	struct int_list *next;
};

/* inserts an id in the list sorted */
struct int_list *insert_sorted(struct int_list *l,int num,unsigned long long b) {
	struct int_list *tmp;

	if (l==NULL) {
		tmp=(struct int_list*)malloc(sizeof(struct int_list));
		tmp->num=num;
		tmp->bytes=b;
		tmp->next=NULL;
		l=tmp;
	} else if (l->bytes>b)
		l->next=insert_sorted(l->next,num,b);
	else if (l->bytes<=b) {
		tmp=(struct int_list*)malloc(sizeof(struct int_list));
		tmp->num=num;
		tmp->bytes=b;
		tmp->next=l;
		l=tmp;
	}
	return l;
}

struct int_list *sort_top(unsigned long long top[MAXUSERS]) {
	int i=0;
	struct int_list *t=NULL;

	for (;i<MAXUSERS;i++)
		if (top[i])
			t=insert_sorted(t,i,top[i]);

	return t;
}

