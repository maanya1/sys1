tar:
	tar -czvf Asst1.tgz Asst1 --exclude=Asst1/.vscode --exclude=Asst1/README.md
	rm -f -R Asst1

untar:
	tar -xzvf Asst1.tgz