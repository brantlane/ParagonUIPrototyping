#pragma once

#include "UObject.h"
#include "Engine/DataTable.h"
#include "Filters/CardFilter.h"
#include "Filters/CardFilterGroup.h"
#include "Filters/CardFilterByStat.h"
#include "Filters/CardFilterMain.h"
#include "CardModel.h"
#include "CardListModel.generated.h"

UCLASS(Blueprintable, BlueprintType)
class DECKBUILDERDESKTOP_API UCardListModel : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<UCardModel*> AllCards;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Card List")
	TArray<bool> FilterStates;

public:

	static UCardListModel* ConstructCardListFromCardDataTable(UDataTable* CardDataTable, UDataTable* StatDataTable);

public:

	UFUNCTION(BlueprintCallable, Category = "Card List")
		virtual void FilterCards();

public:

	// The main filter group
	UPROPERTY()
	UCardFilterMain* RootFilterGroup;

	UFUNCTION(BlueprintCallable, Category = "Card List")
	UCardFilterMain* GetMainFilter() const
	{
		return RootFilterGroup;
	}

public:

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void FilterByBaseStats(const TArray<FText> StatNames);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		TArray<UCardFilter*> GetBaseStatFilters() const;


	UFUNCTION(BlueprintCallable, Category = "Card List")
		void FilterByCostValues(const TArray<int32> CostValues);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		TArray<UCardFilter*> GetCostValueFilters() const;


	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* FilterBySlot(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		UCardFilter* GetSlotFilter() const;


	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveAllFilters();

	UFUNCTION(BlueprintCallable, Category = "Card List")
		void RemoveFilter(UCardFilter* FilterToRemove);

	UFUNCTION(BlueprintCallable, Category = "Card List")
		TArray<UCardFilter*> FindFiltersMatching(FName TypeName, FText DisplayName, FText DisplayValue) const;


	// Get a list of active user filters for displaying in UI
	UFUNCTION(BlueprintCallable, Category = "Card List")
		TArray<UCardFilter*> GetDisplayableFilters() const;

protected: // Filter groups

	UPROPERTY()
		UCardFilterGroup* UserFilterGroup;

protected: // User filters

	UPROPERTY()
		UCardFilterGroup* SlotFilterGroup;

protected:

	void ConstructDefaultFilters();

};
