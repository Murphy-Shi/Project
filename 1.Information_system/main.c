#include "./func.h"

int main(void)
{
	FILE *fd = fopen(PATH, "r");
	jud_fd(fd);
	struct infor *list = (struct infor *)malloc(sizeof(struct infor));
	jud_list(list);
	input_file(list, fd);
	sw_ch(list, fd);

	return 0;
}

