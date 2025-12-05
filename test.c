#include "html_templater.h"


int main() {
	list_node data;
	data.key = "name";
	data.value = "bench";
	list_node data2;
	data2.key = "reps";
	data2.value = "1";
	list_node data3;
	data3.key = "weight";
	data3.value = "100";
	list_node data4;
	data4.key = "rm";
	data4.value = "100";
	data.next = &data2;
	data2.next = &data3;
	data3.next = &data4;
	data4.next = NULL;

	FILE *output_file = fopen("out.html", "w");

	copy_template_to_html("start.html", output_file);
	write_rm_to_html("row_template.html", output_file, &data);
	copy_template_to_html("end.html", output_file);
        return 0;
}
