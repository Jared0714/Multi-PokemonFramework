#include <CTRPluginFramework.hpp>
#include "../../Helpers/Includes/Helpers.hpp"

using namespace CTRPluginFramework;

namespace USUM
{
	u8 Gender = 0;
	u8 SkinTone = 0;
	
	u8 CangeSkinTone(u8 Tone)
	{
		if (Gender == 0x0)
			return (Tone - 0x4);
		
		else return (Tone + 0x4);
	}
	
	u16 MatchingHair(u8 Tone)
	{
		if (Tone == 0x00 || Tone == 0x04)
			return 0x8300;
		
		if (Tone == 0x08 || Tone == 0x0C)
			return 0x0400;
		
		if (Tone == 0x10 || Tone == 0x14)
			return 0x4800;
		
		if (Tone == 0x18 || Tone == 0x1C)
			return 0x0800;
		
		else return 0x0;
	}
	
	// Function to add clothes to inventory and return next empty inventory slot
	u32 AddToClothes(u32 Address, u8 Data, u16 LoopNum)
	{
		for (int i = 0; i < LoopNum; i++)
		{
			if (!WRITE8(Address, Data))
				goto Error;
			
			Address += 0x1;
		}
		
		return(Address);
		Error: return (0);
	}
	
	void FixMakeupBag(void)
	{
		u32 Address = 0x33011FE0;
		u16 Temp;
		
		if (!READ16(Address, Temp))
			goto Error;
		
		if (Gender == 0x0)
		{
			while (Temp)
			{
				if (Temp != 0x06C2)
				{
					Address += 4;
					READ16(Address, Temp);
				}
				
				else
				{
					WRITE32(Address, 0);
					return;
				}
			}
		}
		
		else
		{
			while (Temp)
			{
				if (Temp == 0x06C2)
					return;
				
				else
				{
					Address += 4;
					READ16(Address, Temp);
				}
			}
			
			WRITE16(Address, 0x06C2);
		}
		
		Error: return;
	}
	
	struct Genders
	{
		const char *Name;
		const u8 Value;
	};
	
	static const std::vector<Genders> GenderOptions =
	{
		{"Male", 0x00},
		{"Female", 0x01}
	};
	
	void ChangeGender(MenuEntry *entry)
	{
		static u32 Address = 0x3301281C;
		static std::vector<std::string> optionsGender;
		
		if (optionsGender.empty())
		{
			for (const Genders &g : GenderOptions)
				optionsGender.push_back(g.Name);
		}
		
		if (!READ8(Address + 0x1, Gender))
			goto Error;
		
		if (!READ8(Address + 0x50, SkinTone)) goto Error;
		{
			Keyboard KB(Utils::Format("Current Gender: %s", GenderOptions[Gender].Name), optionsGender);
			int Choice = KB.Open();
			
			if (Choice >= 0 && Choice != Gender)
			{
				Gender = GenderOptions[Choice].Value;
				FixMakeupBag();
				
				if (Gender == 0x0)
				{
					if (!WRITE8(Address + 0x01, Gender))
						goto Error;
					
					if (!WRITE32(Address + 0x50, 0x00800000 + MatchingHair(SkinTone) + CangeSkinTone(SkinTone)))
						goto Error;
					
					if (!WRITE32(Address + 0x54, 0x00040000))
						goto Error;
					
					if (!WRITE32(Address + 0x58, 0x0010040C))
						goto Error;
					
					if (!WRITE16(Address + 0x5C, 0x1C01))
						goto Error;
					
					if (!WRITE8(Address + 0x5E, 0x30))
						goto Error;
				} 
				
				else
				{
					if (!WRITE8(Address + 0x01, Gender))
						goto Error;
					
					if (!WRITE32(Address + 0x50, 0x00800000 + MatchingHair(SkinTone) + CangeSkinTone(SkinTone)))
						goto Error;
					
					if (!WRITE32(Address + 0x54, 0x00040000))
						goto Error;
					
					if (!WRITE32(Address + 0x58, 0x00100405))
						goto Error;
					
					if (!WRITE16(Address + 0x5C, 0x3001))
						goto Error;
					
					if (!WRITE8(Address + 0x5E, 0x30))
						goto Error;
				}
				
				if (!WRITE32(Address + 0x64, 0x00000000))
					goto Error;
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
			
			else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		Error: return;
	}
	
	struct SkinTones
	{
		const char *Name;
		const u8 Value;
	};
	
	static const std::vector<SkinTones> SkinToneOptions =
	{
		{"Pale", 0x00},
		{"Light", 0x08},
		{"Tan", 0x10},
		{"Dark", 0x18}
	};
	
	const char* GetSkinToneName(u8 Tone)
	{ 
		if (Tone == 0x00 || Tone == 0x04)
			return "Pale";
		
		if (Tone == 0x08 || Tone == 0x0C)
			return "Light";
		
		if (Tone == 0x10 || Tone == 0x14)
			return "Tan";
		
		if (Tone == 0x18 || Tone == 0x1C)
			return "Dark";
		
		else return "";
	}
	
	void ChangeSkinTone(MenuEntry *entry)
	{
		static u32 Address = 0x3301281C;
		static std::vector<std::string> optionsSkinTone;
		
		if (optionsSkinTone.empty())
		{
			for (const SkinTones &s : SkinToneOptions)
				optionsSkinTone.push_back(s.Name);
		}
		
		if (!READ8(Address + 0x1, Gender))
			goto Error;
		
		if (!READ8(Address + 0x50, SkinTone)) goto Error;
		{
			Keyboard KB(Utils::Format("Current Skin Tone: %s", GetSkinToneName(SkinTone)), optionsSkinTone);
			int Choice = KB.Open();
			
			if (Choice >= 0)
			{
				if (Gender == 0x00)
				{
					if (!WRITE8(Address + 0x50, SkinToneOptions[Choice].Value))
						goto Error;
				}
				
				else
				{
					if (!WRITE8(Address + 0x50, SkinToneOptions[Choice].Value + 0x04))
						goto Error;
				}
				
				MessageBox("Operation has been completed!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
			}
			
			else MessageBox("Operation has been interrupted!", DialogType::DialogOk).SetClear(ClearScreen::Both)();
		}
		
		Error: return;
	}
	
	void ReceiveAllClothes(MenuEntry *entry)
	{
		u32 Address = 0x33052A30;
		u8 Temp = 0;
		
		// Check if character is male
		if (READ8(0x3301281D, Temp) && Temp == 0x00)
		{
			Address = AddToClothes(Address, 0x01, 0x0040);
			Address = AddToClothes(Address, 0x00, 0x007C);
			Address = AddToClothes(Address, 0x01, 0x0015);
			Address = AddToClothes(Address, 0x00, 0x0009);
			Address = AddToClothes(Address, 0x01, 0x012A);
			Address = AddToClothes(Address, 0x00, 0x0098);
			Address = AddToClothes(Address, 0x01, 0x006C);
			Address = AddToClothes(Address, 0x00, 0x00AD);
			Address = AddToClothes(Address, 0x01, 0x0026);
			Address = AddToClothes(Address, 0x00, 0x0077);
			Address = AddToClothes(Address, 0x01, 0x0061);
			Address = AddToClothes(Address, 0x00, 0x0064);
			Address = AddToClothes(Address, 0x01, 0x006E);
			AddToClothes(Address, 0x00, 0x0043);
			
			Address = 0x33052A30;
			
			if (!WRITE32(Address + 0x1D8, 0x01030101))
				goto Error;
			
			if (!WRITE32(Address + 0x304, 0x01010301))
				goto Error;
			
			if (!WRITE32(Address + 0x4B0, 0x00010301))
				goto Error;
			
			if (!WRITE32(Address + 0x584, 0x00000003))
				goto Error;
		}
		
		// Otherwise if the character is female
		else
		{
			Address = AddToClothes(Address, 0x01, 0x0063);
			Address = AddToClothes(Address, 0x00, 0x0015);
			Address = AddToClothes(Address, 0x01, 0x0025);
			Address = AddToClothes(Address, 0x00, 0x001F);
			Address = AddToClothes(Address, 0x01, 0x0015);
			Address = AddToClothes(Address, 0x00, 0x0009);
			Address = AddToClothes(Address, 0x01, 0x01B4);
			Address = AddToClothes(Address, 0x00, 0x000E);
			Address = AddToClothes(Address, 0x01, 0x00FC);
			Address = AddToClothes(Address, 0x00, 0x001C);
			Address = AddToClothes(Address, 0x01, 0x007E);
			Address = AddToClothes(Address, 0x00, 0x0020);
			Address = AddToClothes(Address, 0x01, 0x00A9);
			Address = AddToClothes(Address, 0x00, 0x001C);
			Address = AddToClothes(Address, 0x01, 0x0092);
			AddToClothes(Address, 0x00, 0x001F);
			
			Address = 0x33052A30;
			
			if (!WRITE32(Address + 0x264, 0x01010103))
				goto Error;
			
			if (!WRITE32(Address + 0x394, 0x01010301))
				goto Error;
			
			if (!WRITE32(Address + 0x3B4, 0x01010103))
				goto Error;
			
			if (!WRITE32(Address + 0x4F8, 0x00010301))
				goto Error;
			
			if (!WRITE32(Address + 0x5A8, 0x00000003))
				goto Error;
		}
		
		Error: return;
	}
}