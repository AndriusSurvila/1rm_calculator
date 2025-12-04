#include "html_templater.h"


int main() {
	rm_data data={"bench press", 200, 5, 233.33};
	rm_data data2={"squat", 250, 3, 283.33};
	copy_template_to_html("start.html", "out.html");
	write_rm_to_html("row_template.html", "out.html", &data);
	write_rm_to_html("row_template.html", "out.html", &data2);
	copy_template_to_html("end.html", "out.html");
        return 0;
}
