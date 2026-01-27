


#include "AbilitySystem/Abilities/AuraPassiveAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"

void UAuraPassiveAbility::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UAuraAbilitySystemComponent* AuraAsc = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo())))
	{
		if (ActorInfo && ActorInfo->IsNetAuthority() && !AuraAsc->ActivatedPassiveAbility.IsBoundToObject(this))
		{
			AuraAsc->ActivatedPassiveAbility.AddUObject(this, &ThisClass::OnPassiveAbilityActivated);
		}
	}
}

void UAuraPassiveAbility::OnPassiveAbilityActivated(const FGameplayTag& AbilityTag, bool bActivate)
{
	if (AbilityTags.HasTag(AbilityTag) && !bActivate)
	{
		UAuraAbilitySystemComponent* AuraAsc = Cast<UAuraAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()));

		if (AuraAsc)
		{
			AuraAsc->ActivatedPassiveAbility.RemoveAll(this);
		}
		
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}
