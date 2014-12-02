// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "FriendsAndChatPrivatePCH.h"
#include "ChatItemViewModel.h"
#include "SChatItem.h"

#define LOCTEXT_NAMESPACE "SChatWindow"

class SChatItemImpl : public SChatItem
{
public:

	void Construct(const FArguments& InArgs, const TSharedRef<FChatItemViewModel>& InViewModel)
	{
		FriendStyle = *InArgs._FriendStyle;
		MenuMethod = InArgs._Method;
		this->ViewModel = InViewModel;

		FText DisplayNameText = ViewModel->GetFriendNameDisplayText();
		if(ViewModel->IsFromSelf())
		{ 
			if (ViewModel->GetMessageType() == EChatMessageType::Whisper)
			{
				FFormatNamedArguments Args;
				Args.Add(TEXT("Username"), ViewModel->GetFriendNameDisplayText());
				DisplayNameText = FText::Format(LOCTEXT("SChatItem_To", "To {Username}"), Args);
			}
		}

		FFormatNamedArguments Args;
		Args.Add(TEXT("DisplayName"), DisplayNameText);
		Args.Add(TEXT("Message"), ViewModel->GetMessage());
		Args.Add(TEXT("NameStyle"), FText::FromString(GetTextHyperlinkStyle()));
		FText DisplayText = FText::Format(LOCTEXT("SChatItem_Message", "<a id=\"UserName\" style=\"{NameStyle}\">{DisplayName}</>{Message}"), Args);

		FTextBlockStyle TextStyle = FriendStyle.TextStyle;
		TextStyle.ColorAndOpacity = GetChannelColor();

		SUserWidget::Construct(SUserWidget::FArguments()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.Padding(FMargin(5,1))
			[
				SNew(SImage)
				.ColorAndOpacity(this, &SChatItemImpl::GetChannelColor)
				.Image(this, &SChatItemImpl::GetChatIcon)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill)
			.Padding(FMargin(5, 1, 2, 1))
			.MaxWidth(FriendStyle.ChatListWidth)
			[
				SNew( SRichTextBlock )
				.Text(DisplayText)
				.TextStyle(&TextStyle)
				.DecoratorStyleSet(&FFriendsAndChatModuleStyle::Get())
				.WrapTextAt(FriendStyle.ChatListWidth - 5)
				+ SRichTextBlock::HyperlinkDecorator(TEXT( "UserName" ), this, &SChatItemImpl::HandleNameClicked)
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.Padding(FMargin(5,1))
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(ViewModel->GetMessageTime())
				.ColorAndOpacity(this, &SChatItemImpl::GetTimeDisplayColor)
				.Font(FriendStyle.FriendsFontStyleSmall)
			]
		]);
	}
private:

	FSlateColor GetTimeDisplayColor() const
	{
		if(ViewModel->UseOverrideColor())
		{
			return ViewModel->GetOverrideColor();
		}
		else
		{
			switch(ViewModel->GetMessageType())
			{
				case EChatMessageType::Global: return FriendStyle.DefaultChatColor.CopyWithNewOpacity(ViewModel->GetFadeAmountColor()); break;
				case EChatMessageType::Whisper: return FriendStyle.WhisplerChatColor.CopyWithNewOpacity(ViewModel->GetFadeAmountColor()); break;
				case EChatMessageType::Party: return FriendStyle.PartyChatColor.CopyWithNewOpacity(ViewModel->GetFadeAmountColor()); break;
				default: return FLinearColor::Gray;
			}
		}
	}

	FSlateColor GetChannelColor () const
	{
		if(ViewModel->UseOverrideColor())
		{
			return ViewModel->GetOverrideColor();
		}
		else
		{
			FSlateColor DisplayColor;
			switch(ViewModel->GetMessageType())
			{
				case EChatMessageType::Global: DisplayColor = FriendStyle.DefaultChatColor; break;
				case EChatMessageType::Whisper: DisplayColor =  FriendStyle.WhisplerChatColor; break;
				case EChatMessageType::Party: DisplayColor =  FriendStyle.PartyChatColor; break;
				default: DisplayColor = FLinearColor::Gray;
			}
			return DisplayColor;
		}
	}

	const FSlateBrush* GetChatIcon() const
	{
		if(ViewModel->UseOverrideColor())
		{
			return nullptr;
		}
		else
		{
			switch(ViewModel->GetMessageType())
			{
				case EChatMessageType::Global: return &FriendStyle.ChatGlobalBrush; break;
				case EChatMessageType::Whisper: return &FriendStyle.ChatWhisperBrush; break;
				case EChatMessageType::Party: return &FriendStyle.ChatPartyBrush; break;
				default:
				return nullptr;
			}
		}
	}

	const FString GetTextHyperlinkStyle() const
	{
		switch(ViewModel->GetMessageType())
		{
			case EChatMessageType::Global: return TEXT("UserNameTextStyle.GlobalHyperlink"); break;
			case EChatMessageType::Whisper: return TEXT("UserNameTextStyle.Whisperlink"); break;
			case EChatMessageType::Party: return TEXT("UserNameTextStyle.PartyHyperlink"); break;
			default:
			return FString();
		}
	}

	void HandleNameClicked( const FSlateHyperlinkRun::FMetadata& Metadata )
	{
		ViewModel->FriendNameSelected();
	}

private:

	// Holds the Friends List view model
	TSharedPtr<FChatItemViewModel> ViewModel;

	TSharedPtr<SBorder> FriendItemBorder;

	/** Holds the style to use when making the widget. */
	FFriendsAndChatStyle FriendStyle;

	// Holds the menu method - Full screen requires use owning window or crashes.
	EPopupMethod MenuMethod;
};

TSharedRef<SChatItem> SChatItem::New()
{
	return MakeShareable(new SChatItemImpl());
}

#undef LOCTEXT_NAMESPACE
