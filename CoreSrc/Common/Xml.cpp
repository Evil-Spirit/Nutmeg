//------------------------------------------------------------------------------
//
// Nutmeg::Core::Engine
//
// copyright:	(c) 2008-2011 One More Studio
// author:		Alexey Egorov (FadeToBlack aka EvilSpirit)
// url:			http://nutmeg-engine.ru
// mail:		anandamide@mail.ru
// icq:			455-761-951
// skype:		fade_to_evil
//
//------------------------------------------------------------------------------

#include "Xml.h"

//------------------------------------------------------------------------------

#include "Debug.h"
#include "File.h"
#include "MathCore.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	Xml::Arg::Arg(const char *name_, const char *data_) {
		name = name_;
		data = data_;
	}

	//--------------------------------------------------------------------------

	Xml::Xml(const char *name) {
		setName(name);
	}

	//--------------------------------------------------------------------------

	Xml::~Xml() {

	}

	//--------------------------------------------------------------------------

	const char *Xml::getName() const {
		return name;
	}

	//--------------------------------------------------------------------------

	void Xml::setName(const char *name_) {
		name = name_;
	}

	//--------------------------------------------------------------------------

	int Xml::getChildrenCount() const {
		return children.count();
	}

	//--------------------------------------------------------------------------

	Xml *Xml::getChild(int i) {
		return &children[i];
	}

	//--------------------------------------------------------------------------

	Xml *Xml::getChild(const char *child) {
		for (int i=0; i<children.count(); i++) {
			if (children[i].name == child) {
				return &children[i];
			}
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	const Xml *Xml::getChild(int i) const {
		return &children[i];
	}

	//--------------------------------------------------------------------------

	const Xml *Xml::getChild(const char *child) const {
		for (int i=0; i<children.count(); i++) {
			if (children[i].name == child) {
				return &children[i];
			}
		}
		return NULL;
	}

	//--------------------------------------------------------------------------

	Xml *Xml::addChild(Xml *xml) {
		children.append(xml);
		return xml;
	}

	//--------------------------------------------------------------------------

	Xml *Xml::addChild(const char *name) {
		Xml *child = new Xml(name);
		children.append(child);
		return child;
	}

	//--------------------------------------------------------------------------

	void Xml::removeChild(int i) {
		children.remove(i);
	}

	//--------------------------------------------------------------------------

	void Xml::removeChild(Xml *xml) {
		children.remove(xml);
	}

	//--------------------------------------------------------------------------

	int Xml::getArgsCount() const {
		return args.count();
	}

	//--------------------------------------------------------------------------

	const char *Xml::getArg(int i) const {
		return args[i].data;
	}

	//--------------------------------------------------------------------------

	const char *Xml::getArg(const char *arg) const {
		int arg_index = findArg(arg);
		if(arg_index < 0) return NULL;
		return args[arg_index].data;
	}

	//--------------------------------------------------------------------------

	bool Xml::isArg(const char *name) const {
		return getArg(name) != NULL;
	}

	//--------------------------------------------------------------------------

	int Xml::findArg(const char *name) const {
		for(int i = 0; i<args.count(); i++) {
			if (args[i].name == name) {
				return i;
			}
		}
		return -1;
	}

	//--------------------------------------------------------------------------

	void Xml::setArg(int i, const char *name, const char *data) {
		args[i].name = name;
		args[i].data = data;
	}

	//--------------------------------------------------------------------------

	void Xml::setArg(const char *name, const char *data) {

		int arg_index = findArg(name);
		if (arg_index != -1) {
			setArg(arg_index, name, data);
		} else {
			args.append(new Arg(name, data));
		}

	}

	//--------------------------------------------------------------------------

	const char *Xml::getData() const { return data; }

	//--------------------------------------------------------------------------

	void Xml::setData(const char *data_) { data = data_; }

	//--------------------------------------------------------------------------

	const char *Xml::parseXml(const char *str) {

		#define IS_SPACE(chr)				(chr == ' ' || chr == '\t')
		#define IS_EOL(chr)					(chr == '\n' || chr == '\r')
		#define IS_EOS(chr)					(chr == '\0')
		#define IS_LETTER(chr)				(chr >= 'a' && chr <= 'z' || chr >= 'A' && chr <= 'Z' || chr == '_')
		#define IS_DIGIT(chr)				(chr >= '0' && chr <= '9')

		#define SKIP_SPACES_NOCHECK(str)   	while (IS_SPACE(*str) || IS_EOL(*str)) str ++;

		#define SKIP_SPACES(str)		   	SKIP_SPACES_NOCHECK(str);								\
											if (IS_EOS(*str)) fatal("Xml::parseXml():");

		#define SKIP_CHAR(str, chr)			{ if (*str != chr) fatal("Xml::parseXml():"); str ++; }

		#define GET_NAME(str, name)			{														\
												if (!IS_LETTER(*str)) fatal("Xml::parseXml():");	\
												*name = '\0';										\
												char *ptr = name;									\
												while (IS_LETTER(*str) || IS_DIGIT(*str)) {			\
													*ptr = *str;									\
													str ++;											\
													ptr ++;											\
												}													\
												*ptr = '\0';										\
												if (IS_EOS(*str)) fatal("Xml::parseXml():");		\
											}

		#define GET_DATA(str, data, term)	{														\
												*data = '\0';										\
												char *ptr = data;									\
												while (!IS_EOS(*str) && *str != term) {				\
													*ptr = *str;									\
													str ++;											\
													ptr ++;											\
												}													\
												*ptr = '\0';										\
												if (IS_EOS(*str)) fatal("Xml::parseXml():");		\
											}

		char name[128];
		char close_name[128];
		static char arg_name[128];
		static char data[16384];

		SKIP_SPACES_NOCHECK(str);
		if (IS_EOS(*str)) return str;

		SKIP_CHAR(str, '<');

		// comment T
		// TODO : add comment reading
		if (*str == '!') {

			SKIP_CHAR(str, '!');
			SKIP_CHAR(str, '-');
			SKIP_CHAR(str, '-');
			// *data = '\0';
			// char *ptr = data;
			while (!IS_EOS(*str)) {
				// *ptr = *str;
				str ++;
				// ptr ++;

				if (str[0] == '-' && str[1] != '\0' && str[1] == '-' && str[2] != '\0' && str[2] == '>') {
					SKIP_CHAR(str, '-');
					SKIP_CHAR(str, '-');
					SKIP_CHAR(str, '>');
					setComment("comment");
					return str;
					//break;
				}

			}
			//*ptr = '\0';
			//if (IS_EOS(*str)) fatal("Xml::parseXml():");

			//setComment(data);
			//SKIP_SPACES(str);
			//SKIP_CHAR(str, '<');
		}

		SKIP_SPACES(str);

		GET_NAME(str, name);

		setName(name);

		SKIP_SPACES(str);

		// get args
		while (IS_LETTER(*str)) {

			GET_NAME(str, arg_name);

			SKIP_SPACES(str);

			SKIP_CHAR(str, '=');

			SKIP_SPACES(str);

			SKIP_CHAR(str, '"');

			GET_DATA(str, data, '"');

			SKIP_CHAR(str, '"');

			setArg(arg_name, data);

			SKIP_SPACES(str);
		}

		// check no data node
		if (str[0] == '/' && str[1] == '>') {
			str += 2;
			return str;
		}

		SKIP_CHAR(str, '>');

		const char *old_str = str;
		SKIP_SPACES(str);

		bool data_node = false;

		if (*str != '<') {

			str = old_str;
			GET_DATA(str, data, '<');
			setData(data);

			data_node = true;

		}

		do {

			SKIP_SPACES(str);

			// parse end tag
			if (str[0] == '<' && str[1] == '/') {

				str += 2;

				SKIP_SPACES(str);

				GET_NAME(str, close_name);

				SKIP_SPACES(str);

				SKIP_CHAR(str, '>');

				if(strcmp(close_name, name) != 0) fatal("Xml::parseXml():");

				return str;
			} else if (data_node) {
				fatal("Xml::parseXml():");
			}

			Xml *child = new Xml("child");
			str = child->parseXml(str);

			// if comment
			if (child->comment != "") {
				delete child;
				continue;
			}

			children.append(child);

		} while (!IS_EOS(*str));

		fatal("Xml::parseXml():");

		#undef IS_SPACE
		#undef IS_EOL
		#undef IS_EOS
		#undef IS_LETTER
		#undef IS_DIGIT
		#undef SKIP_SPACES_NOCHECK
		#undef SKIP_SPACES
		#undef SKIP_CHAR
		#undef GET_NAME
		#undef GET_DATA

     	return str;
	}

	//--------------------------------------------------------------------------

	bool Xml::load(const char *name) {

		File file(name,"rb");

		if (file.opened() == false) {
			return false;
		}

		char *buffer = NULL;
		int size = file.size();
		buffer = new char[size + 1];
		file.readData(buffer,size);
		buffer[size] = '\0';

		read(buffer, size);

		delete [] buffer;
		return true;

	}

	//--------------------------------------------------------------------------

	void Xml::saveToFile(FILE *f, int depth) const {

		if (comment != "") {
			for(int i=0; i<depth; i++) fprintf(f,"\t");
			fprintf(f,"<!--%s-->\n", comment.str());
		}

		for(int i=0; i<depth; i++) fprintf(f,"\t");

		fprintf(f,"<%s", name.str());

		if (args.count() > 0) {
			for (int i=0; i<args.count(); i++) {
				fprintf(f," %s=\"%s\"", args[i].name.str(),args[i].data.str());
			}
		}

		if (children.count() > 0) {
			fprintf(f,">\n");

			for(int i=0; i<children.count(); i++) {
				children[i].saveToFile(f, depth + 1);
			}

			for(int i=0; i<depth; i++) fprintf(f,"\t");
			fprintf(f,"</%s>\n", name.str());

		} else if(data != "") {
			fprintf(f,">%s</%s>\n", data.str(), name.str());
		} else {
			fprintf(f,"/>\n");
		}

	}

	//--------------------------------------------------------------------------

	void Xml::save(const char *name) const {
		FILE *f = fopen(name, "w");
		if (f == NULL) fatal("Xml::save(): cant open file to write.");
		saveToFile(f);
		fclose(f);
	}

	//--------------------------------------------------------------------------

	bool Xml::getArg(const char *name, int &r) const { const char *arg = getArg(name); if (arg) Nutmeg::fromString(arg, r); return arg != NULL; };
	void Xml::setArg(const char *name, int d) { setArg(name, Nutmeg::intToStr(d)); }

	bool Xml::getArg(const char *name, bool &r) const { const char *arg = getArg(name); if (arg) { int i; Nutmeg::fromString(arg, i); r = i; } return arg != NULL; };
	void Xml::setArg(const char *name, bool d) { setArg(name, Nutmeg::intToStr(d)); }

	bool Xml::getArg(const char *name, float &r) const { const char *arg = getArg(name); if (arg) Nutmeg::fromString(arg, r); return arg != NULL; };
	void Xml::setArg(const char *name, float d) { setArg(name, Nutmeg::floatToStr(d)); }

	bool Xml::getArg(const char *name, vec3 &r) const { const char *arg = getArg(name); if (arg) Nutmeg::fromString(arg, r); return arg != NULL; };
	void Xml::setArg(const char *name, const vec3 &d) { setArg(name, Nutmeg::vec3ToStr(d)); }

	bool Xml::getArg(const char *name, quat &r) const { const char *arg = getArg(name); if (arg) Nutmeg::fromString(arg, r); return arg != NULL; };
	void Xml::setArg(const char *name, const quat &d) { setArg(name, Nutmeg::quatToStr(d)); }

	bool Xml::getArg(const char *name, mat4 &r) const { const char *arg = getArg(name); if (arg) Nutmeg::fromString(arg, r); return arg != NULL; };
	void Xml::setArg(const char *name, const mat4 &d) { setArg(name, Nutmeg::mat4ToStr(d)); }

	bool Xml::getArg(const char *name, Str &r) const { r = getArg(name); return true; };

	//--------------------------------------------------------------------------

	void Xml::getData(int &r) const { Nutmeg::fromString(data, r); }
	void Xml::setData(int d) { data = Nutmeg::intToStr(d); }

	void Xml::getData(bool &r) const { int i; Nutmeg::fromString(data, i); r = i;}
	void Xml::setData(bool d) { data = Nutmeg::intToStr(d); }

	void Xml::getData(float &r) const { Nutmeg::fromString(data, r); }
	void Xml::setData(float d) { data = Nutmeg::floatToStr(d); }

	void Xml::getData(vec3 &r) const { Nutmeg::fromString(data, r); }
	void Xml::setData(const vec3 &d) { data = Nutmeg::vec3ToStr(d); }

	void Xml::getData(quat &r) const { Nutmeg::fromString(data, r); }
	void Xml::setData(const quat &d) { data = Nutmeg::quatToStr(d); }

	void Xml::getData(mat4 &r) const { Nutmeg::fromString(data, r); }
	void Xml::setData(const mat4 &d) { data = Nutmeg::mat4ToStr(d); }

	void Xml::getData(Str &r) const { r = data; }

	//--------------------------------------------------------------------------

	bool Xml::getChildData(const char *name, int &r) const { const Xml *child = getChild(name); if (child != NULL) child->getData(r); return child != NULL; }
	void Xml::setChildData(const char *name, int d) { addChild(name)->setData(d); }

	bool Xml::getChildData(const char *name, bool &r) const { const Xml *child = getChild(name); if (child != NULL) child->getData(r); return child != NULL; }
	void Xml::setChildData(const char *name, bool d) { addChild(name)->setData(d); }

	bool Xml::getChildData(const char *name, float &r) const { const Xml *child = getChild(name); if (child != NULL) child->getData(r); return child != NULL; }
	void Xml::setChildData(const char *name, float d) { addChild(name)->setData(d); }

	bool Xml::getChildData(const char *name, vec3 &r) const { const Xml *child = getChild(name); if (child != NULL) child->getData(r); return child != NULL; }
	void Xml::setChildData(const char *name, const vec3 &d) { addChild(name)->setData(d); }

	bool Xml::getChildData(const char *name, quat &r) const { const Xml *child = getChild(name); if (child != NULL) child->getData(r);  return child != NULL; }
	void Xml::setChildData(const char *name, const quat &d) { addChild(name)->setData(d); }

	bool Xml::getChildData(const char *name, mat4 &r) const { const Xml *child = getChild(name); if (child != NULL) child->getData(r); return child != NULL; }
	void Xml::setChildData(const char *name, const mat4 &d) { addChild(name)->setData(d); }

	bool Xml::getChildData(const char *name, Str &r) const { const Xml *child = getChild(name); if (child != NULL) child->getData(r); return child != NULL; }
	void Xml::setChildData(const char *name, const char *d) { addChild(name)->setData(d); }

	//--------------------------------------------------------------------------

	void Xml::setComment(const char *comment_) {
		comment = comment_;
	}

	//--------------------------------------------------------------------------

	const char *Xml::getComment() const {
		return comment;
	}

	//--------------------------------------------------------------------------

	Xml &Xml::operator= (const Xml &o) {

		name = o.name;
		data = o.data;
		comment = o.comment;

		args.clear();
		for (int i=0; i<o.args.count(); i++) {
			setArg(o.args[i].name, o.args[i].data);
		}

		children.clear();
		for (int i=0; i<o.children.count(); i++) {
			Xml *child = addChild(o.children[i].getName());
			*child = o.children[i];
		}

		return *this;

	}

	//--------------------------------------------------------------------------

	void Xml::clear() {
		data = "";
		comment = "";
		args.clear();
		children.clear();
	}

	//--------------------------------------------------------------------------

	void Xml::read(const char *buffer, int size) {

		do {
			comment = "";
			buffer = parseXml(buffer);
		} while (comment != "");

	}

	//--------------------------------------------------------------------------

	void Xml::write(Str &str) {
		writeToStr(str, 0);
	}

	//--------------------------------------------------------------------------

	void Xml::writeToStr(Str &str, int depth) {

		if (comment != "") {
			for(int i=0; i<depth; i++) str += "\t";
			str += "<!--";
			str += comment + "-->\n";
		}

		for(int i=0; i<depth; i++) str += "\t";

		str += "<"; str += name;

		if (args.count() > 0) {
			for (int i=0; i<args.count(); i++) {
				str += " ";
				str += args[i].name + "=\"" + args[i].data + "\"";
			}
		}

		if (children.count() > 0) {
			str += ">\n";

			for(int i=0; i<children.count(); i++) {
				children[i].writeToStr(str, depth + 1);
			}

			for(int i=0; i<depth; i++) str += "\t";
			str += "</";
			str += name + ">\n";

		} else if(data != "") {
			str += ">";
			str += data + "</"+ name + ">\n";
		} else {
			str += "/>\n";
		}
	}

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------
