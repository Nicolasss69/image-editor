build:
	gcc image_editor.c -lm -g -Wall -Wextra -o image_editor
clean:
	rm -r image_editor