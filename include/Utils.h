/* Copyright (C) 2004 Bart
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
 
 
/* UTILS
 * Some stuff i need in a lot of places so i dropped in all together in one file.
 * If you think this approach sucks, dont tell me, i know =)
 */

#ifndef UTILS
#define UTILS

#include <gtkmm/label.h>
#include <glibmm/ustring.h>

#include <sstream>
#include <vector>

namespace GParted
{

typedef long long Sector;

#define MEGABYTE 2048  //try it: 2048 * 512 / 1024 /1024 == 1    :P	


//struct to store filesystems
struct FS
{
	Glib::ustring filesystem ;
	bool supported ; //open/resize/copy
	bool create ; //create (duh =) )
};
	
//globally used convenience functions
inline long Sector_To_MB( Sector sectors ) 
{
	 return (long) ( (double) sectors * 512/1024/1024 +0.5) ;
}

inline long Round( double double_value )
{
	 return (long) ( double_value + 0.5) ;
}

inline Sector Abs( Sector sectors )
{
	return sectors < 0 ? sectors - 2*sectors : sectors ;
}

inline Gtk::Label * mk_label( const Glib::ustring & text, bool use_markup = true, bool align_left = true, bool wrap = false, const Glib::ustring & text_color = "black" ) 
{
	Gtk::Label * label = manage( new Gtk::Label( text ) ) ;
	
	label ->set_use_markup( use_markup ) ;
	
	if ( align_left )
		label ->set_alignment( Gtk::ALIGN_LEFT ) ;
	
	label ->set_line_wrap( wrap ) ;
	
	if ( text_color != "black" )
	{
		Gdk::Color color( text_color ) ;
		label ->modify_fg( label ->get_state(), color ) ;
	}
	
	return label ;
}

inline Glib::ustring num_to_str( Sector number )
{
	std::ostringstream os;
	os .imbue( std::locale("") );
	os << number ;
	return os .str() ;
}

inline bool Supported( const Glib::ustring & filesystem, std::vector<FS> *FILESYSTEMS ) 
{
	for (unsigned int t=0 ; t < FILESYSTEMS ->size() ; t++ )
		if ( (*FILESYSTEMS)[ t ] .filesystem == filesystem && (*FILESYSTEMS)[ t ] .supported )
			return true ;
	
	return false ;
}



}//GParted

#endif //UTILS