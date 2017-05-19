/**
 * @file PMBUSArtProv.cpp
 */
#include "PMBUSArtProv.h"

#include "CommonDef.h"

wxBitmap PMBUSArtProvider::CreateBitmap(const wxArtID& id,
	const wxArtClient& client,
	const wxSize& WXUNUSED(size))
{
	//if (client == wxART_MESSAGE_BOX)
	//{
		if (id == wxART_INFORMATION)
			return LOAD_PNG_RESOURCE(about_16);

#if 0
		if (id == wxART_ERROR)
			return wxBitmap(error_xpm);
		if (id == wxART_WARNING)
			return wxBitmap(warning_xpm);
		if (id == wxART_QUESTION)
			return wxBitmap(question_xpm);
#endif
	//}

	return wxNullBitmap;
}
