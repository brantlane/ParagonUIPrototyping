// Fill out your copyright notice in the Description page of Project Settings.

#include "DeckBuilderDesktop.h"
#include "CardFilterMain.h"

#pragma region Internal

UCardFilterMain::UCardFilterMain(class FObjectInitializer const & ObjectInitializer)
	: Super(ObjectInitializer)
{
	ConstructSubFilters();
}

UCardFilterMain* UCardFilterMain::ConstructCardFilterMain(FName InFilterType, ECardFilterGroupMatching InMatching)
{
	auto Filter = NewObject<UCardFilterMain>(GetTransientPackage(), NAME_None);
	Filter->FilterName = InFilterType;
	Filter->Matching = InMatching;
	return Filter;
}

void UCardFilterMain::ConstructSubFilters()
{
	// Search by text filter, configured by user
	TextFilter = UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Text")), TEXT("CardName"), FString(), false);
	AddFilter(TextFilter);

	// Deck affinity filters, configured by app
	AffinityFilterGroup = UCardFilterGroup::ConstructCardFilterGroup(FName(TEXT("AffinityGroup")), ECardFilterGroupMatching::Any);
	AddFilter(AffinityFilterGroup);
}

#pragma endregion Internal


#pragma region SubFilters

void UCardFilterMain::FilterByText(const FString& Text)
{
	check(TextFilter != nullptr);
	check(TextFilter->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByText: %s"), *Text);
	TextFilter->StatContains = Text;
}

void UCardFilterMain::FilterByAffinities(TArray<FString> AffinityNames)
{
	check(AffinityFilterGroup != nullptr);
	check(AffinityFilterGroup->IsValidLowLevel());
	UE_LOG(Deck, Verbose, TEXT("UCardFilterMain::FilterByAffinities: %s"), *FString::Join(AffinityNames, TEXT(", ")));
	AffinityFilterGroup->RemoveAllFilters();
	for (auto AffinityName : AffinityNames)
	{
		AffinityFilterGroup->AddFilter(UCardFilterByStat::ConstructCardFilterByStat(FName(TEXT("Affinity")), TEXT("Affinity"), AffinityName, false));
	}
}

#pragma endregion SubFilters
