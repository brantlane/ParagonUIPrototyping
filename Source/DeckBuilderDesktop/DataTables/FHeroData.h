#pragma once

#include "Engine/DataTable.h"
#include "FHeroData.generated.h"

USTRUCT(BlueprintType)
struct FHeroData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FHeroData(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		FString HeroName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		UTexture2D* AvatarTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero Data")
		TArray<FString> Affinities;

	friend bool operator==(const FHeroData& LHS, const FHeroData& RHS);
};

