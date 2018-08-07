#include "stdafx.h"

void	CRenderTarget::phase_occq	()
{
	if (Device.m_SecondViewport.IsSecondVpFrame)
		u_setrt(Device.dwWidth, Device.dwHeight, RImplementation.Target->rt_secondVP->pRT, NULL, NULL, /* Ќе знаю, нужен ли он тут*/ HW.pBaseZB); // »зменить ещЄ ширину/высоту и подумать над последним аргументом
	else
		u_setrt(Device.dwWidth, Device.dwHeight, HW.pBaseRT, NULL, NULL, HW.pBaseZB); //здесь наверное тоже, надо проверить.
	RCache.set_CullMode			( CULL_CCW	);
	RCache.set_Stencil			(TRUE,D3DCMP_LESSEQUAL,0x01,0xff,0x00);
	RCache.set_ColorWriteEnable	(FALSE		);
	RCache.set_Shader			( s_occq	);
}
