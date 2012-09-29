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

#ifndef XmlH
#define XmlH

//------------------------------------------------------------------------------

#include "Array.h"
#include "Str.h"
#include "LibApi.h"

//------------------------------------------------------------------------------
//
// namespace Nutmeg
//
//------------------------------------------------------------------------------

namespace Nutmeg {

	//--------------------------------------------------------------------------

	class vec3;
	class mat4;
	class quat;

	//--------------------------------------------------------------------------
	//
	// class Xml
	//
	//--------------------------------------------------------------------------

	class NUTMEG_API Xml {

		struct Arg {

			Str name;
			Str data;

			Arg(const char *name_, const char *data_);

		};

		Str name;
		Str data;
		Str comment;

		Array <Xml> children;
		Array <Arg> args;

	protected:

		const char *parseXml(const char *str);
		void saveToFile(FILE *f, int depth = 0) const;
		void writeToStr(Str &str, int depth);

	public:

		Xml(const char *name);
		virtual ~Xml();

		const char *getName() const;
		void setName(const char *name_);

		//----------------------------------------------------------------------
		// children
		//----------------------------------------------------------------------

		int getChildrenCount() const;

		Xml *getChild(int i);
		Xml *getChild(const char *child);

		const Xml *getChild(int i) const;
		const Xml *getChild(const char *child) const;

		Xml *addChild(Xml *xml);
		Xml *addChild(const char *);

		void removeChild(int i);
		void removeChild(Xml *xml);

		//----------------------------------------------------------------------
		// args
		//----------------------------------------------------------------------

		int getArgsCount() const;

		const char *getArg(int i) const;
		void setArg(int i, const char *name, const char *data);
		bool isArg(const char *name) const;

		int findArg(const char *name) const;

		const char *getArg(const char *name) const;

		bool getArg(const char *name, int &res) const;
		void setArg(const char *name, int data);

		bool getArg(const char *name, bool &res) const;
		void setArg(const char *name, bool data);

		bool getArg(const char *name, float &res) const;
		void setArg(const char *name, float data);

		bool getArg(const char *name, vec3 &res) const;
		void setArg(const char *name, const vec3 &data);

		bool getArg(const char *name, quat &res) const;
		void setArg(const char *name, const quat &data);

		bool getArg(const char *name, mat4 &res) const;
		void setArg(const char *name, const mat4 &data);

		bool getArg(const char *name, Str &res) const;
		void setArg(const char *name, const char *data);

		//----------------------------------------------------------------------
		// data
		//----------------------------------------------------------------------

		const char *getData() const;

		void getData(int &res) const;
		void setData(int data);

		void getData(bool &res) const;
		void setData(bool data);

		void getData(float &res) const;
		void setData(float data);

		void getData(vec3 &res) const;
		void setData(const vec3 &data);

		void getData(quat &res) const;
		void setData(const quat &data);

		void getData(mat4 &res) const;
		void setData(const mat4 &data);

		void getData(Str &res) const;
		void setData(const char *data_);

		//----------------------------------------------------------------------
		// data
		//----------------------------------------------------------------------

		bool getChildData(const char *child, int &res) const;
		void setChildData(const char *child, int data);

		bool getChildData(const char *child, bool &res) const;
		void setChildData(const char *child, bool data);

		bool getChildData(const char *child, float &res) const;
		void setChildData(const char *child, float data);

		bool getChildData(const char *child, vec3 &res) const;
		void setChildData(const char *child, const vec3 &data);

		bool getChildData(const char *child, quat &res) const;
		void setChildData(const char *child, const quat &data);

		bool getChildData(const char *child, mat4 &res) const;
		void setChildData(const char *child, const mat4 &data);

		bool getChildData(const char *child, Str &res) const;
		void setChildData(const char *child, const char *data_);

		//----------------------------------------------------------------------
		// comment
		//----------------------------------------------------------------------

		void setComment(const char *comment);
		const char *getComment() const;

		//----------------------------------------------------------------------
		// save / load
		//----------------------------------------------------------------------

		bool load(const char *name);
		void save(const char *name) const;

		void read(const char *data, int size);
		void write(Str &str);

		//----------------------------------------------------------------------

		void clear();

		//----------------------------------------------------------------------

		Xml &operator= (const Xml &xml);

		//----------------------------------------------------------------------

	};

	//--------------------------------------------------------------------------

}

//------------------------------------------------------------------------------

#endif

//------------------------------------------------------------------------------
